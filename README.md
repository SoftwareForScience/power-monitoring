# How to install a docker-cluster node

1. First of all download the latest raspbian image.
Download this from:
[https://sfs.twizzel.net/images/](https://sfs.twizzel.net/images/) (latest is [twizzel-raspbian-v0.1.6.img](https://sfs.twizzel.net/images/twizzel-raspbian-v0.1.6.tar.gz)).
2. Flash this image on your sd-card or USB-stick.
3. Boot your Raspberry Pi.
4. SSH to you Raspberry Pi.
5. Go to docker-cluster dir and run `init.sh` with `./init.sh` and after a beautifull install, your Raspberry Pi is ready!
6. For example try `python run-md5.py` to run a simple demo (`twizzel/clustermd5sum`).