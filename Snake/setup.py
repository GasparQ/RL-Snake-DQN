from distutils.core import setup, Extension
from glob import glob

qt_env = 'C:/Qt/5.12.2/msvc2017_64/include/'
qt_libs = 'C:/Qt/5.12.2/msvc2017_64/lib/'

module1 = Extension('pySnake',
                    include_dirs = glob('C:/Users/Victor/Anaconda3/envs/GYM_ENV/include')
                    + glob(qt_env)
                    + glob(qt_env + 'QtGui')
                    + glob(qt_env + 'QtWidgets')
                    + glob(qt_env + 'QtCore'),
                    libraries = ['python36', 'Qt5Gui', 'Qt5Widgets', 'Qt5Core'],
                    library_dirs = ['C:/Users/Victor/Anaconda3/envs/GYM_ENV/libs', qt_libs],
                    sources = glob('*.cpp') + glob('./moc_files/*.cpp'))

setup (name = 'PackageName',
       version = '1.0',
       ext_modules = [module1])