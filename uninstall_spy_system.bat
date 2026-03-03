@echo off
chcp 65001 > nul
echo ==========================================
echo    SECRET AGENT SYSTEM UNINSTALLER
echo ==========================================
echo.

echo Step 1: Removing old installation files...
del spy_install_flag.dat 2>nul && echo [REMOVED] Old install flag

echo.
echo Step 2: Removing main program files...
attrib -h -s spy_system_config.dat >nul 2>&1
attrib -h -s spy_agents.dat >nul 2>&1
del spy_system_config.dat 2>nul && echo [REMOVED] Configuration
del spy_agents.dat 2>nul && echo [REMOVED] Agent database

echo.
echo Step 3: Preserving usage history...
echo Usage history maintained in hidden file.
echo Reinstall will continue from previous count.
echo.
echo Files remaining:
dir spy_*.dat /a 2>nul
echo.
pause