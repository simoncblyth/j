#!/usr/bin/env python

import os, re, datetime

class Screenshot(object):
    """
    Handling of AlmaLinux Screenshots which are written to ~/Pictures
    after simple renaming to remove spaces from then name. 
    """
    FMT = "Screenshot_from_%Y-%m-%d_%H-%M-%S.png" 
    _PTN = r"(?P<name>Screenshot_from_(?P<year>\d{4})-(?P<month>\d{2})-(?P<day>\d{2})_(?P<hour>\d{2})-(?P<minute>\d{2})-(?P<second>\d{2}).png)$"
    PTN = re.compile(_PTN)

    @classmethod
    def Parse(cls, name):
        match = cls.PTN.match(name)
        return None if match is None else match.groupdict() 

    @classmethod
    def IsValid(cls, name):
        match = cls.PTN.match(name)
        return not match is None

    @classmethod
    def MakeDatetime(cls, d):
        year = int(d["year"])
        month = int(d["month"])
        day = int(d["day"])
        hour = int(d["hour"])
        minute = int(d["minute"])
        second = int(d["second"])
        return datetime.datetime(year, month, day, hour, minute, second)

    @classmethod
    def MakeName(cls, dt):
        return dt.strftime(cls.FMT)

    def __init__(self, name):
        d = self.Parse(name)
        dt = self.MakeDatetime(d)
        nm = self.MakeName(dt)
        assert nm == d["name"]
        d["dt"] = dt
        d["nm"] = nm
        self.d = d 

    def __repr__(self):
        return " %(name)s %(dt)s " % self.d 


class ScreenshotFold(object):
    def __init__(self, base=os.environ.get("FOLD", ".")):
        l = []
        for name in sorted(os.listdir(base)):
            if not Screenshot.IsValid(name): continue
            sc = Screenshot(name)
            l.append(sc)
        pass
        self.l = l

    def __repr__(self):
       return "\n".join(map(repr, self.l)) 

if __name__ == '__main__':
    scf = ScreenshotFold() 
    print(scf)



