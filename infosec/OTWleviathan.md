# Leviathan
In this write up all the passwords are censored because the website OverTheWire writes in their
rules:
> "Do not publish credentials to any of the games. We understand the need to create writeups,
walkthroughs, and tutorials, but do not publish any credentials."

If I have missed any, please open up an issue on this github repo page.

If you want to play yourself, check the rules first: https://overthewire.org/rules/
and just go on the website and play it from there. 

Okay let's begin.

From the [website](https://overthewire.org/):
```
Dare you face the lord of the oceans?

Leviathan is a wargame that has been rescued from the demise of intruded.net, previously hosted on leviathan.intruded.net. Big thanks to adc, morla and reth for their help in resurrecting this game!

What follows below is the original description of leviathan, copied from intruded.net:

Summary:
	Difficulty:     1/10
	Levels:         8
	Platform:   Linux/x86

Author:
Anders Tonfeldt

Special Thanks:
We would like to thank AstroMonk for coming up with a replacement idea for the last level,
deadfood for finding a leveljump and Coi for finding a non-planned vulnerability.

Description:
This wargame doesn't require any knowledge about programming - just a bit of common
sense and some knowledge about basic *nix commands. We had no idea that it'd be this
hard to make an interesting wargame that wouldn't require programming abilities from 
the players. Hopefully we made an interesting challenge for the new ones.

Leviathan’s levels are called leviathan0, leviathan1, … etc. and can be accessed on leviathan.labs.overthewire.org through SSH on port 2223.
```

# General Notes
mktemp -d for temp dir


# Level 1

To login to the first level use:

Username: `[censored]`
Password: `[censored]`

Data for the levels can be found in the homedirectories. 
You can look at /etc/leviathan_pass for the various level passwords.


Host: leviathan.labs.overthewire.org

Port: 2223

there's a .backup directory with a html file

doing this:
```bash
grep pass bookmarks.html
```
gives us 
```html
<DT><A HREF="http://leviathan.labs.overthewire.org/passwordus.html |
 This will be fixed later, the password for leviathan1 is [censored]"
 ADD_DATE="1155384634" LAST_CHARSET="ISO-8859-1" ID="rdf:#$2wIU71">password
 to leviathan1</A>
```

## pass:
leviathan1:`[censored]`

# Level 2

I'm gonna use strace and ltrace for this 

tho figure out what these program do you can always use: `whatis` 
```
$ whatis strace
strace (1)           - trace system calls and signals

$ whatis ltrace
ltrace (1)           - A library call tracer
```
using strace doesn't give us much, nothing that springs out at me at least
but using ltrace we can see that the program uses strcmp and comperesses
the first three chars of our input with 'sex'
so sex must be the password.

ltrace dump
```
$ ltrace ./check
__libc_start_main(0x80491e6, 1, 0xffffd5e4, 0 <unfinished ...>
printf("password: ")                                    = 10
getchar(0xf7fbe4a0, 0xf7fd6f80, 0x786573, 0x646f67password: [censored]
)     = 103
getchar(0xf7fbe4a0, 0xf7fd6f67, 0x786573, 0x646f67)     = 97
getchar(0xf7fbe4a0, 0xf7fd6167, 0x786573, 0x646f67)     = 109
strcmp("gam", "sex")                                    = -1
puts("Wrong password, Good Bye ..."Wrong password, Good Bye ...
)                    = 29
+++ exited (status 0) +++
```

now that we entered 'sex' into the ./check executable it gives us a shell
denoted by the $ sign, and yes echo $0 tells us that we are running /bin/sh

now because this is a wargame the shell probably has a higher level of 
rights than we do, so running
cat /etc/leviathan_pass/leviathan2
gives us:
`[censored]`

Let's Go!

## pass: 
leviathan2:`[censored]`

# Level 2

There are a few ways to handle this one

We have a executable in the home dir called printfile
it says what it does, it prints a file, now when looking at strace you can 
see that it isn't being validated so you can escape it using something like
a; bash, or a; bash -p to keep the privileges.

after that it's as simple as doing a cat on the file
## pass:
leviathan3:`[censored]`


# Level 3 
Okay we got a file called level3, I'm gonna try using what we've learned
with strace and ltrace.


ltrace dump:
```
ltrace ./level3 
__libc_start_main(0x80492bf, 1, 0xffffd5f4, 0 <unfinished ...>
strcmp("h0no33", "kakaka")                                                                                         = -1
printf("Enter the password> ")                                                                                     = 20
fgets(Enter the password> test
"test\n", 256, 0xf7e2a620)                                                                                   = 0xffffd3cc
strcmp("test\n", "`[censored]`\n")                                                                                    = 1
puts("bzzzzzzzzap. WRONG"bzzzzzzzzap. WRONG
)                                                                                         = 19
+++ exited (status 0) +++
```

Hmm the ltrace tells me it's comparing our input to the string `[censored]`, 
using strcmp(), now I first though that `[censored]`, is some sort of variable,
but nope, it's the password!
so putting it in...

```
/bin/sh

./level3 
Enter the password> `[censored]`
[You've got shell]!
$ echo $0 
/bin/sh
$ 
```

aaaaand we got a shell. 
The name of the password here is meant to throw you off

now that we got a shell, it should have elevated privileges, so let's just cat
the password fort the next level:


```
$ cat /etc/leviathan_pass/leviathan4
[censored]
```
## pass:
leviathan4:`[censored]` 

# Level 4

we have a .trash dir with a ./bin executable
it seems to fopen the leviathan5 password file and it spits out a bunch of binary,
translating the binary to text we get
`[censored]`

## pass:

leviathan5:`[censored]` 

an yes that's the right one! Pretty easy level

# Level 5

got an executable called leviathan 5

executing it we get the following message:
Cannot find /tmp/file.log
creating the log file
echo "test" > /tmp/file.log

We could just link /tmp/file.log to /etc/leviathan_pass/leviathan6
via `ln -s /etc/leviathan_pass/leviathan6 /tmp/file.log`, aaaaand we got a password.

## Pass:
leviathan6:`[censored]` 

# Level 6
We have an executable that wants a 4 number pin code, I think I'll just 
brute force this one, shouldn't take that long.

Let's just input every code from 0000 to 9999.


```for x in {0000..9999}; do ./leviathan6 "$x"; done```

and the password is....

cat /etc/leviathan_pass/leviathan7
`[censored]` 

## Pass:
leviathan7:`[censored]` 

# The End
and we are done!
