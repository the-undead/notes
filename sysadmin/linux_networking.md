# Linux Networking
## ifupdown-ng
I like using ifupdown-ng (https://github.com/ifupdown-ng/ifupdown-ng/blob/main/doc/ADMIN-GUIDE.md)
You mainly edit the /etc/network/interfaces file for your networking needs.

## the 'ip' command
powerfull as hell, here are some commands:

```
ip a add/del <ip>/<cidr> dev <dev-name>

ip link set <dev-name> up/down

ip r add defaul via <ip>

ip r show

ip a show <int>/< >

ip -brief a

ip a flush dev <dev-name>

ip link set dev <dev-name> mtu <576-1500>
```
