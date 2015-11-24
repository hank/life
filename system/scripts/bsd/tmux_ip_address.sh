#!/bin/sh
echo "FOO" > /tmp/a
ifconfig $(route get 8.8.8.8 | awk '/interface:/{print $2}') | awk '/inet /{printf("%s", $2)}'
