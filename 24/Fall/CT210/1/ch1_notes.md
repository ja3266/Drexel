## Deploying Ubuntu Server
An extremely powerful distro of Linux for server and network purposes. Great for setting up any sort of server need like dbs, file servers, or even a minecraft server. 
## Technical Requirements
- 64-bit CPU
- 1 GB RAM
- 10-GB hard disk (16 GB or more is recommended)
## Determining Your Server's Role
Each server in an environment must have some role that's assigned to it. Whether it's a file server, database, web server or whatever, it must have a defined purpose for what it's supposed to add to the organization. 

Now that your server's role has been determined, you can then plan for how to implement it. Certain questions must be answered about the server to determine how to set it up, like if it's a mission critical server we must determine if it needs redundancy for uptime, or if its something like a Goblin box we need to implement it for speed and efficiency in r/w. Just keep in mind some stipulations around the server you're going to implement before you do it. 

## Choosing a Device for our Server
There are many different types of devices that we could install Ubuntu server on. Here are a few examples:
- Physical server
- Physical desktop
- Laptop
- Virtual machine
- Virtual private server
- Raspberry Pi
### Physical Server
Old desktops that don't have a use anymore. Something you're hanging on to and could use as a simple file or web server that has low traffic. Or maybe its one of those small form-factor desktops. These are good options for the home server enthusiast. 

For production environments these are not good ideas. They need to be able to handle higher speeds, more traffic, and have features that typical desktops just don't have. Hardware RAID, ECC memory, multiple processors, and more are just not available to desktops the same way that a dedicated rack mounted server would have. 

### Laptop
Another great option for the home user who wants to experiment or run a Minecraft server or something. They're cost-effective, take up little space, and have all of the essentials preinstalled with it like a keyboard, monitor, mouse, and internals. Obviously these aren't good for professional use. 

### Virtual Machines
VMs are a great way to experiment on an existing computer without having to run a separate unit. You can install Ubuntu server to a program like VirtualBox for free and be up and running in minutes. They are also applicable to large scale production instances, although with much better hardware behind them.

### Virtual Private Server
Cloud VMs. SSH into a VM run by Amazon, Google, or Microsoft for something that it managed and secured by a large-scale cloud provider. It is another good option for someone who may have bigger needs than simply running it on their home desktop, but cannot afford an expensive rack-mounted setup. Could be costly though with monthly subscription fees.

### Raspberry Pi
A great inexpensive favorite for enthusiasts looking to set up a small server. They take up little space, are cheap to get, use little electricity, and can leave them on forever. They can be suprisingly powerful, sometimes moreso that VMs or VPSs. 

## Obtaining Installation Media
1. Get a flash drive (DVD if **absolutely necessary**)
2. Download boot ISO from [https://www.ubuntu.com/download/server](https://www.ubuntu.com/download/server).
3. Download https://etcher.balena.io/
4. Wipe the flash drive
5. Create a boot drive using the ISO on the flash drive in Etcher
Now you have a bootable flashdrive!

## Planning Partitioning Layout
Getting a little ahead of ourselves here, but custom partitions can be used to create custom places for things like networked file shares, Apache web server files, or more. It allows that server's main applications to have their own unadulterated spaces on a drive. 

A clever way to use custom partitioning is to place the user's home directory on its own partition of the drive. This way if the distribution of Linux is changed in any way, the user's files will not be disturbed.

You can also limit applications that use a ton of data to their own partition, thus limiting the amount of space that it can use. This can solve headaches that will pop up down the line if something eats up a ton of space. 

A separate partition for logging could also help, this way if a ton of log files are generated it won't create an issue for the rest of the drive (IE application or data space).

**"Success when maintaining a server is a matter of efficiently managing resources, users, and security—a good partitioning scheme is certainly part of that."**

Here are some other basic partitioning practices:
- At a minimum, a partition for the root filesystem (designated by a forward slash) is required.
- The `/var` directory contains most log files and is therefore a good candidate for separation for the reasons mentioned previously in this section.
- The `/home` directory stores all user files. Separating this into a separate partition can be beneficial as it gives you the possibility of having your user files survive a reinstall of Ubuntu.
- If you’ve used Linux before, you may be familiar with the concept of a **swap partition**, which is a special partition that can act as RAM when your memory becomes full. This is no longer necessary—a **swap file** will be created automatically in newer Ubuntu releases.

## Installing Ubuntu Server
At this point, we have everything we need. We have chosen our server's role, device type, prepared the installation media, and planned our drive partitions. Now we're ready to install.

1. Insert the installation media into the device.
2. Get to BIOS however we can.
3. Choose the flash drive as the boot drive in BIOS
4. Restart
5. The Ubuntu Server installer should appear.
6. Select "Ubuntu Server"
7. Select a language
8. Select a keyboard configuration
9. Select Ubuntu Server (focusing on minimized later)
10. Select DHCP, click done.
11. Enter a Proxy if applicable, otherwise click done.
12. Choose a mirror address if you have another server for providing packages, if not click done. 
13. Select Custom Storage Layout to apply the custom partitioning if you made a plan, if not just use the whole drive.
14. Ensure that the file system is set up correctly, and done to continue.
15. Click continue to erase the drive and continue with the installation.
16. Set up a profile.
17. Enable OpenSSH to be able to remotely manage the server (Good option).
18. Select any applications that are applicable to your server's chosen role.
19. Installation complete!

