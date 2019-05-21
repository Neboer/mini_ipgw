# NEU ipgw manager
help you manage your ipgw network connection.

The neu-ipgw-manager is a light programme which can help you connect to / disconnect from the ipgw network in NEU.
It can check your network status and save your time on ipgw login/logout.

By the way, the program is developed based on ipgw.neu.edu.cn. If you want to do other things with this program,
you can surely change the target website and the post data.

**Welcome to join me to develop this software!** The software is designed and developed by NEU students and will help more NEU
students.
## build
You can download the binary programme directly.
The programme needs [libcurl](https://curl.haxx.se/download.html) library to work properly.
If you use Linux release version such as Ubuntu, you can simply install it via package
 [libcurl4-openssl-dev](https://packages.ubuntu.com/xenial/libcurl4-openssl-dev).


The programme also need [cjson](https://github.com/DaveGamble/cJSON/releases) library to parse json file.
Once it is compiled, it will only need libcurl being installed. The cjson library is static-linked and it doesn't need the user to download.
If you use Linux release version such as Ubuntu, you can simply install it via package
 [libcjson-dev](https://packages.ubuntu.com/disco/libcjson-dev).
 Notice: the ubuntu libcjson-dev package is a bit older than that on github.


You can use cmake to build the programme from source code. The programme contains a cmakelist file and you can build it
by these commands:
```
cmake
```
The package is tested on 64bit Ubuntu 19.04. If you have problems during the build period, please commit a [issue](https://github.com/Neboer/ipgw_linux_c/issues/new) .
## usage
Ipgw manager can be used in many different ways. However, it is quite easy to use and configure.
### basic usage
```
ipgw
```
if you pass no parameters to the programme, the programme will login with the default configure.
```
ipgw -h|--help
```
show help page
```
ipgw -u|--user <username>
```
use a school number as username to login ipgw.

remember this: if you pass no username to the programme, the programme will login with default configure.

If everything is ok, the programme will soon ask you for the password.
```
ipgw -u <username> -p|--password <password>
```
pass password to ipgw either.**Unrecommend!**
```
ipgw -s|--status
```
show status of the NEU ipgw network connection.

For example, if you are connected to the internet through NEU ipgw with wire
, the programme will return "Ethernet NEU Internet". 
```
ipgw -o|--offline
```
offline yourself from ipgw.

### easy configure
```
ipgw -c|--configure <configure-option>(optional)
```
show the configuration of the programme.

```
ipgw --configure <configure-option>=<value>
```
change the configuration of the programme.

You can easily change many options of the programme. The software prepares a lot of settable
options to you so that you can let it do many things as you want.
```
ipgw --edit-configure
```
open the configure file with your default text editor.

Don't forget to run the following command to let it work.
```
ipgw --save-configure
```
### configuration file
by default, the configuration file is ~/ipgw/settings.json
You can set the default username(student number) and your password in it.

You can also set the default account of the NEU network centre website [ipgw.neu.edu.cn:8800](http://ipgw.neu.edu.cn:8800/)
 
 and so on ...
