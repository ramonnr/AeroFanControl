# AeroFanControl
AeroFanControl (AFC)
Written for Gigabyte Aero14 (7700HQ/1060) and Linux running BIOS FW:FB0E and EC FW: F007 
AFC is pretty likely to work on other Gigabyte machines, but tread safely, check in windows if its using the same registers before running AFC.

AFC was inspired by https://github.com/jertel/p37-ec which does pretty much the same thing but with a cli. 
So if you prefer a cli go to said link, also it's gonna be way more convenient to build. You need to mod it for the Cool/Gaming mode though.

AFC depends on the kernel module ec_sys being installed and running with the parameter write_support=1.
If ec_sys is loaded as a lkm then just run
$sudo modprobe ec_sys write_support=1
Else if it's a static module (which it is on Manjaro for example) then you need to set the parameter before it's loaded.
To try it out enter grub and edit the kernel parameters for the kernel you will run. 
On the line that starts with 'linux' go to the end, do a space and write => ec_sys.write_support=1
Once your booted and AFC is built you need to run it with root privileges, this is due to that the Embedded controller (EC) registers are only read/writable under root.

If things does not work, like say for example your running a different Gigabyte model, then read along. 
I would suggest that you boot into windows (guessing your like me here and have a small partition for playing PUBG and updating BIOS).
Then run a program like RWEverything (http://rweverything.com/) in order to inspect the EC registers.
Then run Gigabyte smart manager and play with it and check what registers are changed. 
Then modify AFC to write to said registers with said values. 

AFC is written in Qt5, I'd say smoothest is downloading qtcreator, but I'm gonna guess you can install libraries and headers from your packagemanager.
If building from source is a dealbreaker let me know (ramonnr@kth.se) and I'll try to figure out how to distribute a binary.

Lastly a small interview with myself:
Q: Why did you (I) write AFC?
A: It annoyed the crap out of me that the fans never were silent on linux, so you know hack it. Also I wanted to brush up on 
my Qt skills.
Q: Why does AFC look like... well not pretty? 
A: I'm an embedded developer, ux really is not my strong suite
Q: Why does AFC make everything laggy?
A: Unclear on this, but I get the same behaviour in windows with RWE when reading the EC registers.
Q: I want features, or theres bugs or I want to let you know exactly how crappy the UX is, how do I do any of that?
A: Shoot me an email at ramonnr@kth.se (and I know, no one does but you can if you want to)
