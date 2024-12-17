# UNIX подобные системы.

Operating System Components:

* *The Kernel* - the only program that can interact to hardware.
* *Core Libraries*.
* *Supplement Services*.
* *User interaction environment*.

*Process* - any program instance running in the system. (app, daemons, commands)

Commands to observe:

ps -A; pstree

systemd, init - процесс, запускающий ядро системы.

## Unix Programs

* Binary executables.
* Any text files starting with # (python, shell scripts...)

## Unix users

* The only privileged user: root (UID = 0)
* UID не создаются динамически

## The Boot Process

1. Boot loader - privilged. Загрузчик. Задача: найти образ ядра.
2. The Kernel - priviliged. Ядро.
3. First non-privileged process. (Iinit systemd).
4. Rest scripts and daemos.

## Services (Daemons)

* Might have dependencies on each other.
* Most systems minimum set:
  - dhclient - сеть.
  - getyy - виртуальные терминалы.
  - sshd - удаленное подключение.
  - crond - задачи по расписанию.
  - ntpd or chronyd - синхронизация времени.
  - syslogs - логирование.

## Командный интерпритатор.

Для исполнения команды используется программа-интерпритатор.

## System daemon (systemd)

Start services in concurent way.

## User session: classic  UNIX way.

* Multisets.
* Each user session has it's own terminal

## Background Task

* No associated terminal. (nohup - перехват SIGHUP)
* Output sent by mail.
* No check for single-instance.
