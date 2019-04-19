# NEU ipgw manager
help you manage your ipgw network connection.

The neu-ipgw-manager is a compressed programme to help you connect/disconnect the ipgw network in NEU.
It can check your network status and save your time on ipgw login/logout.

By the way, the program is developed based on ipgw.neu.edu.cn.If you want to do other things with this program,
you can sure change the target website and post data content.

Welcome to help me with the software developing!The software is designed by NEU students and will help more NEU
students.
## usage
Ipgw managener can be used in many different ways, it can help you a lot.
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

If everything is ok, the programme will soon ask you for password.
```
ipgw -u <username> -p|--password <password>
```
pass password to ipgw either.**Unrecognized!**
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
ipgw -c|--configure
```
show the configuration of the programme.

```
ipgw --configure <configure-option>=<value>
```
change the configuration of the programme.

You can easily change many options of the programme.The software prepare a lot of settable
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
You can set the default username(student number) and your password.

You can also set the default account of the NEU network center website [http://ipgw.neu.edu.cn:8800/].
 
 and so on ...
  