set location=C:\U4L\Snip\Core
set projectname=ProjCoreRep
set projectdirname=ProjCoreRep
set projectdir=%location%\%projectdirname%
set sniploc=C:\U4L\snip\
set TargUtil=%sniploc%SetTargUtil.bat
set ModePostfix=_Main
start /B %TargUtil% %projectname% %projectdir% %ModePostfix%
