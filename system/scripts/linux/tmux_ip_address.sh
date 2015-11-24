#!/bin/sh
ip route get 8.8.8.8 | awk '/src\s+[0-9]/{print $7}'
