# Beginning
In this write up all the passwords are censored because the website OverTheWire writes in their
rules:
> "Do not publish credentials to any of the games. We understand the need to create writeups,
walkthroughs, and tutorials, but do not publish any credentials."

If I have missed any, please open up an issue on this github repo page.

If you want to play yourself, check the rules first: https://overthewire.org/rules/
and just go on the website and play it from there. 
 If you are playing "somegame", then:

    * USERNAMES are somegame0, somegame1, ...
    * Most LEVELS are stored in /somegame/.
    * PASSWORDS for each level are stored in /etc/somegame_pass/.


mktemp -d to make temporary directory, /tmp is regularry wiped, don't keep anything
there.


## Be nice
	* don't leave orphan processes running
    * don't leave exploit-files lying around
    * don't annoy other players
    * don't post passwords or spoilers
    * again, DONT POST SPOILERS!
      This includes writeups of your solution on your blog or website!


# Security 
Some security features are enabled on the machine

The following
  compiler flags might be interesting:

    -m32                    compile for 32bit
    -fno-stack-protector    disable ProPolice
    -Wl,-z,norelro          disable relro


# the machine
- 64 bit processor

# Tools installed on the machine

    * gef (https://github.com/hugsy/gef) in /opt/gef/
    * pwndbg (https://github.com/pwndbg/pwndbg) in /opt/pwndbg/
    * peda (https://github.com/longld/peda.git) in /opt/peda/
    * gdbinit (https://github.com/gdbinit/Gdbinit) in /opt/gdbinit/
    * pwntools (https://github.com/Gallopsled/pwntools)
    * radare2 (http://www.radare.org/)
		* Both python2 and python3 are installed.
# Let us begin

ls of /home/ gives
### ls /home/
	bandit0   bandit18  bandit27      bandit31-git  drifter1   drifter6     krypton1
	bandit1   bandit19  bandit27-git  bandit32      drifter10  drifter7     krypton2
	bandit10  bandit2   bandit28      bandit33      drifter12  drifter8     krypton3
	bandit11  bandit20  bandit28-git  bandit4       drifter13  drifter9     krypton4
	bandit12  bandit21  bandit29      bandit5       drifter14  formulaone0  krypton5
	bandit13  bandit22  bandit29-git  bandit6       drifter15  formulaone1  krypton6
	bandit14  bandit23  bandit3       bandit7       drifter2   formulaone2  krypton7
	bandit15  bandit24  bandit30      bandit8       drifter3   formulaone3  ubuntu
	bandit16  bandit25  bandit30-git  bandit9       drifter4   formulaone5
	bandit17  bandit26  bandit31      drifter0      drifter5   formulaone6

We are doing bandit, so let's keep it in bandit, I'm unsure why there are /git files

### hostnamectl
	 Static hostname: bandit
	       Icon name: computer-vm
	         Chassis: vm
	      Machine ID: ec22625a89d9cae2a146b7bb0a1d19ce
	         Boot ID: a7452da9ee0a45e5bc259f2cc6a28a01
	  Virtualization: amazon
	Operating System: Ubuntu 22.04.2 LTS              
	          Kernel: Linux 5.19.0-1023-aws
	    Architecture: x86-64
	 Hardware Vendor: Amazon EC2
	  Hardware Model: t3.medium

### The find command
Search for files which are executable but not readable.

`$ find /sbin /usr/sbin -executable \! -readable -print`


   -user uname
              File is owned by user uname (numeric user ID allowed).

same with

	-group groupname


# Levels

## Level 0
there is a readme with the contents:
`[censored]`

## Level 1
password is located in a file called '-'
open it using 'cat < -' 
Pass:
`[censored]`
## Level 2

Filename with spaces in it,
solved with ' cat spaces\ in\ this\ filename '
pass: `[censored]`

## Level 3
file loaction is in /home/bandit3/inhere/.hidden
file is hidden so use 'ls -a'
then use 'cat .hidden'
pass:`[censored]` 

## Level 4
Now this level is a bit complicated
we need to find a human readable file in a directory filled with files called 
'-file{00..09}'
okay so I check the file mime type using this 

```bash
for f in *; do file --mime-type -- "$f"; done
```

this gives us that 07 and 09 are plain text

the -- is to parse the file so 'file' doesn't shit it's fucking pants

after that we can cat the two files with `cat -- -file07`

we see that 09 looks weird so we use 07, I haven't found a better check yet 
as this password looks like the other ones.

We can also just run strings on the whole dir using something like
 ```bash
for f in *; do strings -- "$f"; done
```
there we see all the human readable strings, we get a few but again 07 looks the
most like a password

Password: `[censored]`


## Level 5 

Okay so we have a bunch of directories in /inhere
these are all filled with files

we are searching for a specific file, one that has the following properties

- human-readable
- 1033 bytes in size
- not executable


### Solution
`find inhere/ -size 1033c -readable \! -executable`
 
the c is for bytes, the \t is to remove executable from the serach

Password: `[censored]`

## Level 6

Properties:
- owned by user bandit7
- owned by group bandit6
- 33 bytes in size

So the File is stored somewhere on the server not in inhere/, but anywhere
I tried running
`find / -size 33c -group bandit6 -user bandit7 `
gave a bunch of permission denied errors,
so I need to figure out how to figure out how to check what I've got acess to.

okay the command was fine the error messages where just too much, we 
did not need to check what we've got acess too either

just do this to pipe errors to dev/null
`find / -user bandit7 -group bandit6 -print 2>/dev/null`
this gave us the location of the password file
/var/lib/dpkg/info/bandit7.password

Password: `[censored]`

## Level7

We have a file called data.txt, it appears to be filled with data, probably tsv

The password for the next level is stored in the file data.txt next to the word millionth

wow just a grep is enough to solve this
```bash
$ grep millionth data.txt 
millionth   [censored]
```
Password:`[censored]`

## Level 8 
Same setup as before, got a data.txt

### Goal
The password for the next level is stored in the file data.txt 
and is the only line of text that occurs only once

### Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd


### Approach
the command uniq seems to spell unique, so checking the man page
it says, yes, it prints ore ommits unique or repeating lines!
So it's perfect for this

uniq -u 

uniq apperently only checks if the line is duplicate next to it and doesn't check
the whole ass file for a line, so we first have to sort it!

This means we just do a sort

`sort data.txt | uniq -u`

Password: `[censored]`

## Level 9

The password for the next level is stored in the file data.txt 
in one of the few human-readable strings, preceded by several ‘=’ characters.

so whe just use strings and grep 

```bash
$ strings data.txt | grep ==
4========== the#
========== password
========== is
========== [censored]
```
Password: `[censored]`

## Level10
data.txt looks base64 encode

so we use 

```bash
base64 -d data.txt
```
to decode
and we get:" The password is `[censored]` "

Password: `[censored]`

## Level 11 
Looks like a ceaser cipher or just a shift idk

### Goal
The password for the next level is stored in the file data.txt,
where all lowercase (a-z) and uppercase (A-Z) letters 
have been rotated by 13 positions

### Approach
I think tr can do that

okay lookint at the wikipedia page for rot13, which is the encryption
here
https://en.wikipedia.org/wiki/ROT13
we can see that Vim can do that shit lol

in Vim we can do ggg?G to rot13 something

`vim data.txt`

`ggg?G`

et voilà

Password: `[censored]`

## Level 12
### Goal
The password for the next level is stored in the file data.txt, 
which is a hexdump of a file that has been repeatedly compressed.
 For this level it may be useful to create a directory under /tmp
 in which you can work using mkdir. For example: mkdir /tmp/myname123.
 Then copy the datafile using cp, and rename it using mv (read the manpages!)

### Approach
We make a tmp dir with mktemp

copy over data.txt

#### Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd, mkdir, cp, mv, file

Password `[censored]`

## Level 13

### Goal
The password for the next level is stored in /etc/bandit_pass/bandit14 
and can only be read by user bandit14. 
For this level, you don’t get the next password, 
but you get a private SSH key that can be used to log into the next level.
>Note: localhost is a hostname that refers to the machine you are working on

### Approach


while already logged in with ssh we do 

ssh bandit14@localhost -i sshkey.private -p 2220

than just cat the file

Password: `[censored]`

## Level 14
### Level Goal

The password for the next level can be retrieved by submitting 
the password of the current level to port 30000 on localhost.

### Commands needed
ssh, telnet, nc, openssl, s_client, nmap

### Approach 
I think we use nc here

`nc localhost 30000``

now we send `[level 14 password]`

Return:
```
Correct!
[censored]
```
Password: `[censored]`

## Level 15

### Level Goal

The password for the next level can be retrieved by submitting the
password of the current level to port 30001 on localhost using SSL encryption.


### Approach
Same thing we just did, just with SSL encryption

Okay I didn't get how, but now I've got it.

I thought we need nc but nope we use `openssl s_client`

we use this command: `openssl s_client -connect localhost:30001`

Password: `[censored]`

## Level 16

### Level Goal
The credentials for the next level can be retrieved by submitting 
the password of the current level to a port 
on localhost in the range 31000 to 32000. 
First find out which of these ports have a server listening on them.
 Then find out which of those speak SSL and which don’t.
 There is only 1 server that will give the next credentials, 
the others will simply send back to you whatever you send to it.

### Approach

We use this command
`nmap -p 31000-32000 localhost`

`nmap port start-end on localhost`


Password:

Correct!
```
-----BEGIN RSA PRIVATE KEY-----

[censored]

-----END RSA PRIVATE KEY-----

closed
```
## Level 17

### Goal

There are 2 files in the homedirectory: passwords.old and passwords.new. 
The password for the next level is in passwords.new and is the only line
 that has been changed between passwords.old and passwords.new

NOTE: if you have solved this level and see ‘Byebye!’ when trying
 to log into bandit18, this is related to the next level, bandit19


diff passwords.old passwords.new

pass: `[censored]`

## Level 18

### Goal

### Approach
use ssh -p 2220 -T bandit18@bandit.labs.overthewire.org 

the T flag disables pseudo terminal stuff so the bashrc isn't loaded


password: `[censored]`

## Level 19
### Goal
To gain access to the next level, you should use the setuid binary
 in the homedirectory. Execute it without arguments to find out how
 to use it. The password for this level can be found in the usual place 
(/etc/bandit_pass), after you have used the setuid binary.

the bin in the home can be used to run a command as another user
so we just do
```
./bandit20-do cat /etc/bandit_pass/bandit20
```

Password: `[censored]`

## Level 20
### Goal
There is a setuid binary in the homedirectory
that does the following: it makes a connection 
to localhost on the port you specify as a
commandline argument. It then reads a line
of text from the connection and compares it
to the password in the previous level (bandit20).
If the password is correct, it will transmit the
password for the next level (bandit21).

NOTE: Try connecting to your own network daemon to see if it works as you think

### Approach

start a tmux session
start nc -l someport
and start the program on the same
enter the password into the program
and it will send it to our nc server

Password: `[censored]`

## Level 21
### Goal
A program is running automatically at regular intervals from cron, the time-based job scheduler. Look in /etc/cron.d/ for the configuration and see what command is being executed.

### Approach
```bash
bandit21@bandit:~$ cat /etc/cron

cron.d/       cron.daily/   cron.hourly/  cron.monthly/ crontab       cron.weekly/
 
bandit21@bandit:~$ cat /etc/cron.d/cronjob_bandit22

@reboot bandit22 /usr/bin/cronjob_bandit22.sh &> /dev/null
* * * * * bandit22 /usr/bin/cronjob_bandit22.sh &> /dev/null

# we see that bandit22 has a script that is running and 
# piping itself to /dev/null, so let's check it out

bandit21@bandit:~$ cat /usr/bin/cronjob_bandit22.sh

#!/bin/bash
chmod 644 /tmp/somefile
cat /etc/bandit_pass/bandit22 > /tmp/somefile

# The script is chmodding some temp file and piping the level 22
# password to it, we also see that the cronjob runs every minute
# so we can just check this temp file

bandit21@bandit:~$ cat /tmp/somefile
[censored]
# and we got the password
```

Password: `[censored]`

## Level 22
### Goal

A program is running automatically at regular intervals from cron, 
the time-based job scheduler. Look in /etc/cron.d/ for the configuration 
and see what command is being executed.

NOTE: Looking at shell scripts written by other people is a 
very useful skill. The script for this level is intentionally made easy
 to read. If you are having problems understanding what it does,
 try executing it to see the debug information it prints.
 

### Approach
This one was a bit weird, the cronjob wasn't run
so I ran the script and it gave me access to write the passwordfile
to the tmp dir.

`[censored]`

Now we have the password for our current user.

And we also get this bash script:
```bash
#!/bin/bash

myname=$(whoami)
mytarget=$(echo I am user $myname | md5sum | cut -d ' ' -f 1)

echo "Copying passwordfile /etc/bandit_pass/$myname to /tmp/$mytarget"

cat /etc/bandit_pass/$myname > /tmp/$mytarget
```
that means we take the location that we get from mytarget for bandi23
`mytarget=$(echo I am user bandit23 | md5sum | cut -d ' ' -f 1)``

we get: [somefilename]

cat /tmp/[somefilename]
`[censored]`

Password: `[censored]`

## Level 23

### Goal
A program is running automatically at regular intervals from cron, 
the time-based job scheduler. Look in /etc/cron.d/ for the
 configuration and see what command is being executed.

NOTE: This level requires you to create your own first shell-script.
 This is a very big step and you should be proud of yourself when
 you beat this level!

NOTE 2: Keep in mind that your shell script is removed once
 executed, so you may want to keep a copy around…
### Approach

We have this script running on a cronjob
```bash
#!/bin/bash

myname=$(whoami)

cd /var/spool/$myname/foo || exit 1
echo "Executing and deleting all scripts in /var/spool/$myname/foo:"
for i in * .*;
do
    if [ "$i" != "." -a "$i" != ".." ];
    then
        echo "Handling $i"
        owner="$(stat --format "%U" ./$i)"
        if [ "${owner}" = "bandit23" ]; then
            timeout -s 9 60 ./$i
        fi
        rm -rf ./$i
    fi
done
```

Now le'ts write a "shell-script", if you could even call it that.
```bash
#!/bin/bash
cat /etc/bandit_pass/bandit24 > /tmp/somefile.txt
```
chmod +x it

et voilà

pass: [censored]

## Level 24
### Goal
A daemon is listening on port 30002 and will give you 
the password for bandit25 if given the password for bandit24
 and a secret numeric 4-digit pincode. There is no way to
 retrieve the pincode except by going through all of the 10000
 combinations, called brute-forcing.
You do not need to create new connections each time

### Approach

mktemp -d


our command
```bash
for x in {0000..9999}; do echo 'censored' $x; done | nc localhost 30002 | grep -v Wrong; exit
```
it works!

Password: `[censored]`

## Level 25
Okay this one is quite complicated.

After some googling I found out that the shell for this one is `more`
so we need to make our terminal small so more won't just
quit instantly.

after doing that we can press v to open vim in `more`, then we just point
vim to the /etc/password file

password: `[censored]`

then we use vim to set our shell

:set shell=/bin/bash

:shell


## Level 26
just run the command and cat the pass

pass: `[censored]`

## Level 27

just git clone that 

1. Make temp
2. git clone ssh://bandit27-git@localhost:2220/home/bandit27-git/repo 
3. profit


The password to the next level is: `[censored]`

## Level 28
### Goal
There is a git repository
 at ssh://bandit28-git@localhost/home/bandit28-git/repo 
via the port 2220. The password for the user bandit28-git 
is the same as for the user bandit28.

Clone the repository and find the password for the next level.

so just

git clone ssh://bandit28-git@localhost:2220/home/bandit28-git/repo 

we got a markdown file with following contents:

```
# Bandit Notes
Some notes for level29 of bandit.

## credentials

- username: bandit29
- password: xxxxxxxxxx
```
We can just check the commit history via `git log`,
and we find a commit that is called 'fix info leak'

By simply reverting the commit 'fix info leak'
we get the password 

git revert

now we check the markdown file again aaaand:

pass: `[censored]`

## Level 29

### Goal
There is a git repository at
 ssh://bandit29-git@localhost/home/bandit29-git/repo 
via the port 2220. The password for the user bandit29-git
 is the same as for the user bandit29
.
### Approach

We got another file that says no passwords in prod, so we just 
switch branches to dev

to list branches
`git branch -r`

to switch branches

`git checkout dev`


password: `[censored]`

## Level 30
more git stuff
### Approach
git clone ssh://bandit30-git@localhost:2220/home/bandit30-git/repo


okay I've seen in the packed-refs that there was a tag called secret
so I did a fetch, after that we've got a tag

no apperently there are anotated tags in git so after the new tag
was added 
we can just run

`git show secret` and get

`[censored]`


password: `[censored]`

## Level 31
yeah so push a certain file to master and you get the msg with the password

`[censored]`

## Level 32
it makes every command uppercase
now I didn't know this but you can run $0 to run the last command in a shell
so I ran bash
and then $0
got to the etc dir and got me my password:  `[censored]`

## The End
 And that's it, there aren't any more levels
