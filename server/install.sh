#!/bin/bash


echo 'ln -sf /usr/local/src/pixelboard/server/pixelboard-server.sh /usr/local/bin/pixelboard-server'
ln -sf /usr/local/src/pixelboard/server/pixelboard-server.sh /usr/local/bin/pixelboard-server

echo
echo 'cp /usr/local/src/pixelboard/server/pixelboard-server.init.d /etc/init.d/pixelboard-server'
cp /usr/local/src/pixelboard/server/pixelboard-server.init.d /etc/init.d/pixelboard-server

echo
echo 'update-rc.d pixelboard-server defaults'
update-rc.d pixelboard-server defaults

echo
service pixelboard-server restart
