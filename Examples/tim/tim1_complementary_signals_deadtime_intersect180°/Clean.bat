::rd  /S /Q settings        
::以上为删除整个文件夹并确认删除
del Backup* /Q /S

del /f /s /q settings\*.*
del /f /s /q Debug\List\*.*
del /f /s /q Debug\Obj\*.*   
::以上为删除文件夹里所有文件
::del *.ewt /Q /S
del *.crf /Q /S
del *.o   /Q /S
del *.d   /Q /S

del *.out /Q /S
del *.sim /Q /S
del *.lst /Q /S
del *.map /Q /S

del *.pbi    /Q /S
del *.pbd    /Q /S
del *.cout   /Q /S
del *.browse /Q /S

del *.axf /Q /S
del *.htm /Q /S
del *.sct /Q /S
del *.dep /Q /S

del *.uvguix.*   /Q /S
del JLinkLog.txt /Q /S
del *.scvd       /Q /S

del *.iex /s
del *.tra /s
del *.bak /s
del *.ddk /s
del *.edk /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s

del *.opt /s  
::允许删除JLINK的设置
del *.plg /s
del *.rpt /s
del *.tmp /s
del *.__i /s

:: by cheng
exit