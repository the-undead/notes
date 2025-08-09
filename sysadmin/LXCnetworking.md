# LXC Networking

> flockport is so fucking awesome, they have such good posts

## Bridges 
Bridges are used ot connect VMs to a network.

> **Bridges**: Sort of like a software switch \
> They are a basic function of the linux kernel and are ussuallz created with the bridge-utils package

There are two types of bridges you can configure:
- **Host Bridge**: vms/ containers are directly connected ot the host network and appear like any other physical machne on the network
- **NAT**: Subnet is created within the Host with **private** IPs for the containers, this is a NAT bridge.


### Bridged Mode
Bridges containers to host's physical interface, like the 'eth0' interface. 

This type of bridge has the same layer 2 network as the host.

The container will also get an ip from the home routers dhcp. Makes sense because the Host isn't running a DHCP server.

> Now the question for my project is: What would I use to bridge the host and the container to simulate real world 

A sample /etc/network/interfaces config for a bridge: 
```bash
auto br0
iface br0 inet dhcp
bridge_ports eth0
bridge_stp off
bridge_fd 0
bridge_maxwait 0
```

Now you can set static ips either using the home router and doing a dhcp lease using the mac addresses of the container, or just using the containers network settings.

### NAT
> I think a NAT might be what I should use for my lab setup

A NAT exists as a private subnet, it is not bridged to the Hosts eth0

It creates a private network within the hosts computer with the container getting a private ip.

LXC ships with a NAT bridge by default called "lxcbr0".

Setup by the "lxc-net script" in "/etc/init.d/lxc.net" in debian
or "/etc/default/lxc.net.conf" in ubuntu.

In alpine it's at: ... no idea, probablyi n the init system directory.

you can view bridges with:
```
brctl show
```

```
lxc.network.type = veth
lxc.network.flags = up
lxc.network.link = lxcbr0
lxc.network.name = eth0
lxc.network.hwaddr = 00:16:3e:f9:d3:03
lxc.network.mtu = 1500
```

The containers are configured to connect to this bridge via their config files, and get IPs on this private subnet.

> Is that like facilitated just using a script, like do they keep a tally of ips assigned and just give a free one or does lxc do some dhcp shit? Probably the first one.

Okay the lxc-net script does three things: 
- setup dnsmasq to serve dhcp on the bridge
- sets up iptable rules (masquerade)

What the /etc/init.d/lxc-net script does:
```
1. brctl addbr lxcbr0 ----- adds bridge
2. ifconfig lxcbr0 10.0.3.1 netmask 255.255.255.0 up ----- gives the bridge an IP and brings it up
3. Starts a dnsmasq instance with a specified interface lxcbr0 with DHCP subnet range 10.0.3.2-10.0.3.254
4. iptables -t nat -A POSTROUTING -s 10.0.3..0/24 ! -d 10.0.3.0/24 -j ACCEPT ----- Adds an iptables masquerading rule for lxcbr0 so containers can access the net
```

To access the container beyond the host, you'd need you need to do a port forward.

If you are on an internal network, you can connect the containers between hosts with the IP route utility.
With a command like: 
`ip route add ip/sub via ip`

for this kind of routing to work the container subnets need to be different. 

## VPN
Via ipsec and gre you can connect two containers across several hosts across layer 3.

## layer 2 through a layer 3 tunnel - distributed virtual switch
How? Ethernet over GRE or l2tpv3. Plus you can use ipsec to encrypt the tunnels. 
> Is this possible with wiregurad too?



## Sources
- https://archives.flockport.com/flockport-labs-use-lxc-containers-as-routers/

- https://archives.flockport.com/lxc-networking-guide/

## Read Later
https://www.reddit.com/r/Proxmox/comments/vdi7ea/comment/iclqkna/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button