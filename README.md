# centos-openvz-vnc
centos
centos服务端配置vnc桌面环境一键脚本
yum install nano -y; yum update -y; yum upgrade -y; yum install tigervnc-server -y; yum groupinstall "Desktop" -y; yum install firefox -y; rpm -ivh http://linuxdownload.adobe.com/adobe-release/adobe-release-x86_64-1.0-1.noarch.rpm; rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-adobe-linux; yum install flash-plugin nspluginwrapper alsa-plugins-pulseaudio libcurl -y; echo 'echo "nameserver 8.8.8.8" >> /etc/resolv.conf; ' >> /etc/rc.local; echo 'VNCSERVERS="1:root"' >> /etc/sysconfig/vncservers; echo 'VNCSERVERARGS[1]="-geometry 1000x700"' >> /etc/sysconfig/vncservers; vncpasswd; chkconfig vncserver on --level 345; reboot;
附上digitalocean注册链接https://m.do.co/c/dbf220598f6a
