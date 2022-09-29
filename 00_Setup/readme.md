# Raspberry Pi setup

## Making the SD card

TBD

## Headless setup

TBD

# NodeRed setup

Connect to the raspberry pi via SSH and type:

```console
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

This command will install the newest version of NodeJS, NodeRed, and (optionally) the RaspberryPi specific nodes.

To automatically start use these commands:
```console
sudo systemctl enable nodered.service
sudo systemctl start nodered.service
```

From now NodeRed will start automatically at system startup.

NodeRed can be accessed via this URL (the IP address of the Raspberry Pi
is, for example 192.168.1.25):

> http://192.168.1.25:1880


The dashboard UI can be accessed via:

> http://192.168.1.25:1880/ui

Note that these services can be accessed only through HTTP (and **not** HTTPS), via port 1880.

# Docker setup

After installing and starting docker, execute:

On Linux:

```console
docker run -it -p 1880:1880 -v ~/.node-red:/data --name mynodered nodered/node-re
```

on Windows:

```console
docker run -it -p 1880:1880 -v "c:\node-red":/data --name mynodered nodered/node-re
```

