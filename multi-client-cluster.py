from concurrent.futures import ThreadPoolExecutor
import docker
import random
def fun(message, client):
    container = client.containers.run("twizzel/clustermd5sum", environment=["var=%s" % message], detach=True)
    logs = container.logs()
    
    for line in container.logs(stream=True):
        print (line.strip())
client1 = docker.DockerClient(base_url='tcp://192.168.1.6:4243',  tls=False)
client2 = docker.DockerClient(base_url='tcp://192.168.1.7:4243',  tls=False)
client3 = docker.DockerClient(base_url='tcp://192.168.1.8:4243',  tls=False)
client4 = docker.DockerClient(base_url='tcp://192.168.1.9:4243',  tls=False)



pool = ThreadPoolExecutor(50)
clients = [client1,client2,client3,client4]

messages= [
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d",
"c4ca4238a0b923820dcc509a6f75849b",
"c4ca4238a0b923820dcc509a6f758491",
"c4ca4238a0b923820dcc509a6f75849c",
"c4ca4238a0b923820dcc509a6f75849d"
]

 
for my_message in messages:
    client = random.choice(clients);
    future = pool.submit(fun, (my_message), client )
