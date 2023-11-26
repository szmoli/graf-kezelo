@echo off

setlocal

set FILTER_ROOT_DIR=%~dp0..\docs\latex

echo [FILTER] Removing all _source files...
for /R "%FILTER_ROOT_DIR%" %%F IN (*_source.tex) DO (
	del %%F
)

echo [FILTER] Filtering _source from refman.tex...

echo. > "%FILTER_ROOT_DIR%\refman2.tex"
for /F "tokens=*" %%L IN (%FILTER_ROOT_DIR%\refman.tex) DO (
	echo "%%L" | findstr /R /C:"\input{.*_source}" /I > nul

	:: if the line doesn't match the above, print it to the file
	if ERRORLEVEL 1 (
		echo "%%L" | findstr /R /C:"\printindex" /I > nul

		if ERRORLEVEL 1 (
			echo %%L >> "%FILTER_ROOT_DIR%\refman2.tex"
		)
	)
)

echo [FILTER] Overwriting refman.tex...
move "%FILTER_ROOT_DIR%\refman2.tex" "%FILTER_ROOT_DIR%\refman.tex"

echo [FILTER] Filtering complete

endlocal