----------------------------------------Базовая настройка
R1

en
conf t
int gigabitEthernet 0/0/0
ip address 192.168.1.1 255.255.255.0
no sh

exit
int gigabitEthernet 0/0/1
ip address 192.168.2.1 255.255.255.0
no sh

exit
int serial 0/1/0
ip address 192.168.250.1 255.255.255.0
no sh

exit
exit
en
conf t
hostname R1
line con 0
password 1234 
login local
exit

username admin01 privilege 15 secret s1234
exit

R2

en
conf t
int gigabitEthernet 0/0/0
ip address 172.16.1.1 255.255.255.0
no sh

exit
int gigabitEthernet 0/0/1
ip address 172.16.2.1 255.255.255.0
no sh

exit
int serial 0/1/0
ip address 192.168.250.2 255.255.255.0
no sh


--------------------------------------Выполнение задания

https://itexamanswers.net/4-1-3-5-packet-tracer-configure-standard-ipv4-acls-answers.html
https://www.youtube.com/watch?v=47Rg95t_aIo&ab_channel=TechAcad
