# CISCO Networking

Basically all you really need is a combination of `?`,`show` and `conf t` and you can do pretty much everything.
No but really here are some commands:

grep but on cisco:
```
show run | sec <pattern>
```

```
show ip interface brief
```

```
show vlan-switch brief
```

```
show ip route
```
more readable I think:
```
show run | sec route
```

show dhcp leases:
```
show ip dhcp binding
```

check if vdsl is synchronized
```
show controller vdsl 0
```

Debbuging:

```
term mon
```
and then use he `debug` command with a ? to find what you want to debug