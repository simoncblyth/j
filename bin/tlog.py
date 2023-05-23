#!/bin/bash -l 
"""
tlog.py
==========


"""
import os, subprocess, numpy as np

class TLog(object):
    BEGIN = "### SniperProfiling ###"
    END = "###"

    @classmethod
    def Read(cls, path, N=10):
        """
        :param path:
        :param N:
        :return raw: string output from grep, with the  N lines after BEGIN

        Example grep commans::
    
           grep -A 10 "### SniperProfiling ###" /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/ntds2.tlog 

        """
        return subprocess.check_output(['grep','-A',str(N),cls.BEGIN, path ]).decode("utf-8")

    @classmethod
    def FindFirstDigit(cls, line):
        """
        :param line:
        :return column: index of first digit OR -1 if no digits found
        """
        col = -1
        for i, c in enumerate(line):
            if c.isdigit():  
                col = i
                break 
            pass
        pass
        return col  

    @classmethod
    def Parse(cls, raw):
        """
        :param raw:
        :return lines: list of lines selected from raw until ending on line starting with END
        """
        lines = [] 
        for i, line in enumerate(raw.split("\n")):
            lines.append(line)
            if i > 1 and line.startswith(cls.END): break
        return lines

    @classmethod
    def ExtractData(cls, lines):
         """
         :param lines:
         :return dlines: lines containing digits 
         """
         dlines = [] 
         for line in lines:
             dig = cls.FindFirstDigit(line)
             if dig == -1: continue
             dlines.append(line[dig:])
         pass
         return "\n".join(dlines)

    @classmethod
    def Convert(cls, path):
        """
        :param path: to log file 

        Greps and parses log,  converting SniperProfile block 
        into NumPy array that is saved alongside the log. 

        TLog
        log_path: /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/ntds2.tlog 
        npy_path: /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/ntds2.tlog.npy 

        ############################## SniperProfiling ##############################
        Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
        GenTools                 10          161.59400      16.15940     3.15138      
        DetSimAlg                10          24356.36060    2435.63606   55.23210     
        Sum of junotoptask       10          24518.24683    2451.82468   56.78315     
        #############################################################################

        shape:    (3, 4) 
        array([[   10.   ,   161.594,    16.159,     3.151],
               [   10.   , 24356.361,  2435.636,    55.232],
               [   10.   , 24518.247,  2451.825,    56.783]])

        """
        tl = cls(path)
        print(str(tl))
        tl.save()
        return tl.a

    def __init__(self, log_path):
        raw = self.Read(log_path)   
        lines = self.Parse(raw)
        data = self.ExtractData(lines)
        nrow = len(data.split("\n"))   
        a = np.fromstring(data, sep=" ").reshape(nrow, -1)

        self.log_path = log_path 
        self.npy_path = log_path + ".npy" 
        self.raw = raw
        self.lines = lines
        self.data = data 
        self.a = a 

    def save(self):
        np.save(self.npy_path, self.a )

    def __str__(self):
        return "\n".join(["TLog", 
                         "log_path: %s " % self.log_path, 
                         "npy_path: %s " % self.npy_path, 
                         "",
                         "\n".join(self.lines), 
                         "",
                         "shape:    %s " % str(self.a.shape), 
                         repr(self.a) ])
       
    def __repr__(self):
        return "\n".join(self.lines) 
        
if __name__ == '__main__':
    a = TLog.Convert(os.environ["TLOG_PATH"])


