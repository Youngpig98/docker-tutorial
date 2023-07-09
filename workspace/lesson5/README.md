# 容器的端口映射机制

​	`docker run -d centos:6.9 tail -f /etc/hosts`    后面一行命令可以让centos一直在后台运行，所以容器不会挂掉。

​	只要一启动docker服务，宿主机的网卡上就会多出一个docker0网卡。

​	在docker容器内开启的服务器服务，通过外网是无法直接访问的，只有宿主机可以访问，所以需要做一个端口映射。  iptables命令可以手动映射（在宿主机中设置）。

​	最好是在docker run的时候加入-p参数指定端口

​	`sysctl -a | grep ipv4 | grep forward` 	  **查看内核转发参数值**

​	`systemctl status docker` 							**查看docker服务状态**

​	**重点：在每次启动docker服务时，内核转发参数会被设为1，然而当虚拟机被挂起后再开机，该值会自动变为0，然而docker仍在运行中，但是容器已经上不了网了。**



`sysctl net.ipv4.ip_forward=1`  将内核转发参数设为1，主要是目的是当Linux主机有多个网卡时一个网卡收到的信息是否能够传递给其他的网卡。如果设置成1的话，可以进行数据包转发，可以实现VxLAN 等功能。

上述命令可能只是对当前系统生效，如需永久生效可以使用以下命令：

```shell
#可以在/etc/sysctl.conf这个文件里面增加以下内容
net.ipv4.ip_forward = 1  

#然后使用sysctl -p 的命令将参数生效
sysctl -p /etc/sysctl.conf

#然后重新启动网络即可
systemctl restart network
```

​	

**`netstat -lntup` 查看端口监听状况**