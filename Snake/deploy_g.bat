call F:\Anaconda\Scripts\activate.bat
call conda activate dl3

mkdir moc_files

E:\Qt5.12\5.12.2\msvc2017_64\bin\moc.exe snakegame.h -o moc_files/snakegame_moc.cpp
E:\Qt5.12\5.12.2\msvc2017_64\bin\moc.exe widget.h -o moc_files/widget_moc.cpp

pip install .
pause