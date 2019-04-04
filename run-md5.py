import hashlib
import docker
client = docker.from_env()
messages= ["c4ca4238a0b923820dcc509a6f75849b", "c4ca4238a0b923820dcc509a6f758491", "c4ca4238a0b923820dcc509a6f75849c", "c4ca4238a0b923820dcc509a6f75849d"]
for message in messages: 
    
    container = client.containers.run("twizzel/clustermd5sum", environment=["var=%s" % message], detach=True)
    print(container.logs())
