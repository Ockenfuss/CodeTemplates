import numpy as np
import sys
import configparser
import os
import __main__
import datetime
VERSION="1.4.0"



class Input(object):
    """Parser to read inputfiles and create logs.

    Example usage:\n
    import argparse
    VERSION="1.1"
    par=argparse.ArgumentParser()
    par.add_argument('infile')
    par.add_argument('number', type=int)
    par.add_argument('-s',action='store_true')
    args=par.parse_args()
    inp=Inp.Input(args.infile,version=VERSION)
    inp.convert_type(int, "option2")
    """

    def __init__(self,infilename, version, def_opts={}):
        """Create Input parser.

        Arguments:
            object {Input} -- the parser object\n
            infilename {str} -- the file with the input options. Set to 'None' if not given.\n
            version {str} -- version of the program\n

        Keyword Arguments:
            def_opts {dict} -- dictionary with default input options and values. (default: {{}})
        """
        self.filename=infilename
        self.version=version
        self.options={}
        self.config = configparser.ConfigParser()
        self.config._interpolation = configparser.ExtendedInterpolation()
        for sec in def_opts:
            self.options[sec]={}
            for key in def_opts[sec]:
                self.options[sec][key]=def_opts[sec][key]
        if infilename is not None:
            self.config.read(infilename)
        for sec in self.config:
            if not (sec in self.options):
                self.options[sec]={}
            for key in self.config[sec]:
                self.options[sec][key]=self.config[sec][key]

    def getKey(self, option, section):
        """Check the existence of the given keys and choose defaults if they are 'None'."""
        if section==None:
            section="DEFAULT"#possibility to specify standard section
        if option==None:
            option=list(self.options[section].keys())[0]#possibility to specify standard option
        option=option.lower()
        return option, section

    def listKeys(self, section):
        if section==None:
            section=="DEFAULT"
        return self.options[section].keys()
    def get(self,  option=None,section=None):
        """Return the specified option.

        Keyword Arguments:
            option {string} -- The option to be returned. (default: {First option})
            section {string} -- The section where the option is located. (default: {First section})

        Returns:
            value -- value for the given option in the given section 
        """
        option, section=self.getKey(option, section)
        return self.options[section][option]

    def set(self, value, option=None, section=None):
        """Set an option to a specific value.

        Arguments:
            value {obj} -- Value to be placed in the options dictionary.

        Keyword Arguments:
            option {str} -- Option to be set. (default: {None})
            section {str} -- Section where the option is located. (default: {None})
        """
        option, section=self.getKey(option, section)
        self.options[section][option]=value

    def convert_type(self, dtype, option=None, section=None):
        """Convert an input option from string to a given type.

        Arguments:
            dtype {type} -- Either int, float, or bool.

        Keyword Arguments:
            option {string} -- The option to be converted. (default: {None})
            section {string} -- The section where the option is located (default: {None})
        """
        option, section=self.getKey(option, section)
        myDict={int: lambda sec, opt: int(self.get(opt, sec)), float: lambda sec, opt: float(self.get(opt, sec)), bool: lambda sec, opt: self.get(opt, sec).lower() in ("true", "yes", "1", "t")}
        self.set(myDict.get(dtype)(section, option),option=option, section=section)

    def convert_array(self, dtype, option=None, section=None, sep=",", removeSpaces=False):
        """Convert an input option from string to an array of the given type.

        Arguments:
            dtype {type} -- Type to convert the array element, e.g. str, int, float

        Keyword Arguments:
            option {string} -- The option to be converted. (default: {None})
            section {string } -- The section where the option is located (default: {None})
            sep {string} -- The separator between the array values (default: {","})
            removeSpaces {bool} -- Remove spaces in the elements when converting to string array. (default: {False})
        """
        option, section=self.getKey(option, section)
        if dtype==str:
            array=self.options[section][option].split(sep)
            if removeSpaces:
                array=[x.strip() for x in array]
        else:
            array=np.fromstring(self.options[section][option], sep=sep, dtype=dtype)
        self.set(array, option, section)

    def create_log(self):
        """Create a log of the Input object.

        Example:
        Program: Progam1.py
        Version: 1.0.0
        Input options: Config1.ini
        **************************
        ---DEFAULT---
        **************************
        ---Sec1---
        user: 1.0

        Returns:
            array -- array with lines including linebreak.
        """
        log=[]
        log.append("#"+str(datetime.datetime.now()))
        log.append("cd "+os.getcwd())
        log.append("python3 "+" ".join(sys.argv))
        log.append("#Program: "+__main__.__file__)
        log.append("#Version: "+str(self.version))
        log.append("#Input options: "+str(self.filename))
        log.append("#**************************")
        for sec in self.options.keys():
            log.append("#---"+str(sec)+"---")
            for opt in self.options[sec].keys():
                log.append("#"+str(opt)+": " + str(self.get(opt,sec)))
        log=[l+"\n" for l in log]
        return log

    def show_data(self):
        """Print log."""
        print(*self.create_log())

    def check(self):
        """Perform a consistency check on the input options."""
        everything_ok=True
        #if(something_wrong):
            # everything_oK=False
        return everything_ok

    def write_log(self, new_logs, old_logs=[], file_ext=None):
        """Write log to files.

        Combine all old logfiles, append the log of the actual program and save them to all new locations given.

        Arguments:
            old_logs {arr} -- array with old logfiles
            new_logs {arr} -- array with new logfiles to be created.

        Keyword Arguments:
            file_ext {str} -- if set, the file extensions in the given logfile locations are replaced by 'file_ext' before the function is executed. (default: {None})
        """
        old_logs=np.atleast_1d(old_logs)
        new_logs=np.atleast_1d(new_logs)
        if file_ext!=None:
            file_ext=file_ext.strip(".")
            old_logs=[os.path.splitext(logfile)[0]+"."+file_ext for logfile in old_logs]
            new_logs=[os.path.splitext(logfile)[0]+"."+file_ext for logfile in new_logs]

        old_lines=[]
        log=self.create_log()
        for old in old_logs:
            oldfile=open(old)
            old_lines.extend(oldfile.readlines())
            old_lines.append("\n##############################################################")
            oldfile.close()
        old_lines.append("\n##############################################################\n")
        # old_lines=[l for l in old_lines]
        for new in new_logs:
            newfile=open(new, "w")
            newfile.writelines(old_lines)
            newfile.writelines(log)
            newfile.close()


