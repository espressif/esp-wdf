#!/usr/bin/env python3
#
# Copyright 2023 Espressif Systems (Shanghai) PTE LTD
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import socket
import struct
import random
import sys

class message(object):
    COAP_GET = 1
    COAP_POST = 2
    COAP_PUT = 3
    COAP_DELETE = 4

    COAP_TCP_RAW = 0
    COAP_UDP_RAW = 1
    REQUEST_PACKET = 2
    RESPONSE_PACKET = 3
    INSTALL_WASM_APP = 4

    FMT_ATTR_CONTAINER = 99
    FMT_APP_RAW_BINARY = 98

    ID_HOST = -3
    ID_APP_MGR = -2

    VERSION = 1

    LEADING = [0x12, 0x34]

    RESPONSE_HDR_LEN = 8

    ATTR_TYPE_SHORT = 1
    ATTR_TYPE_INT = 2
    ATTR_TYPE_INT64 = 3
    ATTR_TYPE_BYTE = 4
    ATTR_TYPE_UINT16 = 5
    ATTR_TYPE_FLOAT = 6
    ATTR_TYPE_DOUBLE = 7
    ATTR_TYPE_BOOLEAN = 8
    ATTR_TYPE_STRING = 9
    ATTR_TYPE_BYTEARRAY = 10

    ATTR_PACKET_LEN_MIN = 16

    DEFAULT_ADDRESS = '127.0.0.1'
    DEFAULT_PORT = 8888
    DEFAULT_TYPE = 'wasm'
    DEFAULT_HEAP = 8096
    DEFAULT_TIMERS = 20
    DEFAULT_WATCHDOG = 3 * 60 * 1000

class request(message):
    def request_message_pack(self, msg_type, action, format, url, payload=None):
        mid = random.randint(0, 65536)

        payload_len = 0
        if payload:
            payload_len = len(payload)
        
        url_data = url.encode() + b'\0'

        message_payload  = struct.pack('=BB', self.VERSION, action)
        message_payload += struct.pack('!hIihI', format, mid, 0, len(url_data), payload_len)
        message_payload += url_data
        if payload:
            message_payload += payload

        message  = struct.pack('=BB', self.LEADING[0], self.LEADING[1])
        message += struct.pack('!HI', msg_type, len(message_payload))
        message += message_payload
        return message

    def install_app_request(self, parser):
        if parser.file is None:
            raise Exception('-f <App File> should be input')

        url  = '/applet?name=%s'%parser.install
        if parser.type != self.DEFAULT_TYPE:
            url += '&type=%s'%parser.type
        if parser.heap != self.DEFAULT_HEAP:
            url += '&heap=%d'%parser.heap
        if parser.timers != self.DEFAULT_TIMERS:
            url += '&timers=%d'%parser.timers
        if parser.watchdog != self.DEFAULT_WATCHDOG:
            url += '&wd=%d'%parser.watchdog
        payload = parser.file.read()
        message = self.request_message_pack(self.INSTALL_WASM_APP, self.COAP_PUT, self.FMT_APP_RAW_BINARY, url, payload)
        return message

    def uninstall_app_request(self, parser):
        url = '/applet?name=%s'%parser.uninstall
        if parser.type != self.DEFAULT_TYPE:
            url += '&type=%s'%parser.type
        message = self.request_message_pack(self.REQUEST_PACKET, self.COAP_DELETE, self.FMT_ATTR_CONTAINER, url)
        return message

    def query_app_request(self, parser):
        url = '/applet?name=%s'%parser.query 
        message = self.request_message_pack(self.REQUEST_PACKET, self.COAP_GET, self.FMT_ATTR_CONTAINER, url)
        return message

    def query_all_app_request(self, parser):
        url = '/applet'
        message = self.request_message_pack(self.REQUEST_PACKET, self.COAP_GET, self.FMT_ATTR_CONTAINER, url)
        return message

    def __init__(self, parser):
        if parser.install:
            self.request = self.install_app_request(parser)
        elif parser.uninstall:
            self.request = self.uninstall_app_request(parser)
        elif parser.query:
            self.request = self.query_app_request(parser)
        else:
            self.request = self.query_all_app_request(parser)

    def request_bytes(self):
        return self.request

class response(message):
    def response_message_unpack(self, buffer):
        if len(buffer) < self.RESPONSE_HDR_LEN:
            return False

        if buffer[0:len(self.LEADING)] != bytes(self.LEADING):
            return False

        self.msg_type, self.length = struct.unpack('!HI', buffer[len(self.LEADING):self.RESPONSE_HDR_LEN])
        if self.length != len(buffer) - self.RESPONSE_HDR_LEN:
            return False

        message_payload = buffer[self.RESPONSE_HDR_LEN:]
        self.version, self.status = struct.unpack('=BB', message_payload[0:2])
        if self.version != self.VERSION:
            return False
        self.format, self.mid, self.reciever, self.payload_len = struct.unpack('!hIiI', message_payload[2:16])
        self.payload = message_payload[16:]
        self.decode_attr(self.payload)
        return True

    def decode_attr(self, buffer):
        if len(buffer) < self.ATTR_PACKET_LEN_MIN:
            self.desc = None
            return

        flags, total_len, tag_len = struct.unpack('=HIH', buffer[0:8])
        buffer = buffer[8:]
        tag = buffer[0:tag_len - 1].decode('utf-8')
        buffer = buffer[tag_len:]
        attr_num = struct.unpack('=H', buffer[0:2])[0]
        payload = buffer[2:]

        self.desc = dict()
        for i in range(0, attr_num):
            k_len = struct.unpack('=H', payload[0:2])[0]
            payload = payload[2:]
            k = payload[0:k_len - 1].decode('utf-8')
            payload = payload[k_len:]
            t = struct.unpack('=B', payload[0:1])[0]
            payload = payload[1:]

            if t == self.ATTR_TYPE_SHORT:
                v = struct.unpack('=h', payload[0:2])[0]
                payload = payload[2:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_INT:
                v = struct.unpack('=i', payload[0:4])[0]
                payload = payload[4:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_INT64:
                v = struct.unpack('=q', payload[0:8])[0]
                payload = payload[8:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_UINT16:
                v = struct.unpack('=H', payload[0:2])[0]
                payload = payload[2:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_FLOAT:
                v = struct.unpack('=f', payload[0:4])[0]
                payload = payload[4:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_DOUBLE:
                v = struct.unpack('=f', payload[0:8])[0]
                payload = payload[8:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_BOOLEAN:
                v = struct.unpack('=?', payload[0:1])[0]
                payload = payload[1:]
                self.desc[k] = v
            elif t == self.ATTR_TYPE_STRING:
                v_l = struct.unpack('=H', payload[0:2])[0]
                payload = payload[2:]
                v = payload[0:v_l - 1].decode('utf-8')
                payload = payload[v_l:]
                self.desc[k] = v
            else:
                raise Exception('KV type is not supported')

    def __init__(self, request):
        self.data = b''

    def parser(self, data):
        self.data += data
        return self.response_message_unpack(self.data)

    def __str__(self):
        data = 'response status %d\n'% self.status
        if self.desc:
            data += '{\n'
            for i in self.desc:
                if type(self.desc[i]) == str:
                    data += '\t\"%s\":\t\"%s\",\n'%(i, self.desc[i])
                elif type(self.desc[i]) == int:
                    data += '\t\"%s\":\t%d,\n'%(i, self.desc[i])
                else:
                    raise Exception('Desc type is not supported')
            data += '}'
        return data

class transport:
    def __init__(self, parser):
        port = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        port.connect((parser.address, parser.port))
        self.port = port
        self.recvdata = b''

    def send(self, message):
        return self.port.send(message)

    def recv(self):
        RECV_SIZE = 512
        return self.port.recv(RECV_SIZE)

def operator(parser):
    req = request(parser)
    resp = response(req)
    port = transport(parser)

    port.send(req.request_bytes())

    while True:
        data = port.recv()
        if len(data) <= 0:
            break

        ret = resp.parser(data)
        if ret:
            print(resp)
            break

def main():
    msg = message()

    parser = argparse.ArgumentParser()

    # General Options

    install_group = parser.add_argument_group('install an application')
    uninstall_group = parser.add_argument_group('uninstall an application')
    query_group = parser.add_argument_group('query application information')

    install_group.add_argument(
        '--install', '-i',
        help='Install an application',
        metavar='<App Name>',
        type=str)

    uninstall_group.add_argument(
        '--uninstall', '-u',
        help='Uninstall an application',
        metavar='<App Name>',
        type=str)

    query_group.add_argument(
        '--query', '-q',
        help='Query an applications if APP name is given or all applications',
        metavar='<App Name>',
        nargs='?')

    # Control Options

    parser.add_argument(
        '--address', '-S',
        help='Set server address, default to %s'%(msg.DEFAULT_ADDRESS),
        type=str,
        metavar='<Address>',
        default=msg.DEFAULT_ADDRESS)

    parser.add_argument(
        '--port', '-P',
        help='Set server port, default to %d'%(msg.DEFAULT_PORT),
        type=int,
        metavar='<Port>',
        default=msg.DEFAULT_PORT)

    install_group.add_argument(
        '--file', '-f',
        help='Specify app binary file path',
        metavar='<App File>',
        type=argparse.FileType('rb'))

    # Notes

    parser.add_argument(
        '--type',
        help='Type of app',
        type=str,
        metavar='<App Type>',
        choices=['wasm',],
        default=msg.DEFAULT_TYPE)

    install_group.add_argument(
        '--heap',
        help='Heap size of app',
        metavar='<Heap Size>',
        type=int,
        default=msg.DEFAULT_HEAP)

    install_group.add_argument(
        '--timers',
        help='Max timers number app can use',
        metavar='<Timers Number>',
        type=int,
        default=msg.DEFAULT_TIMERS)

    install_group.add_argument(
        '--watchdog',
        help='Watchdog interval in ms',
        metavar='<Watchdog Interval>',
        type=int,
        default=msg.DEFAULT_WATCHDOG)

    args = parser.parse_args()
    operator(args)

def _main():
    try:
        main()
    except (RuntimeError, TypeError, NameError) as e:
        print('\nA fatal error occurred: %s' % e)
        sys.exit(2)

if __name__ == '__main__':
    _main()
