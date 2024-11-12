

jcv SJCLSanchorConstruction



Greetings,

Thank you so much for the advise. Yes, indeed I can see multiple instances
where people emphasize using separate volumes instead of union and multiunion
in the Geant4 forum. I am now trying to implement the cracks using separate
volumes for the inner surface. acrylic being the mother volume can be done
easily.

But I am still divided on how to implement on the outer surface where I have to
place the inverted-cones in acrylic but a portion of the cones' base will
extend out to the waterpool because of spherical shell and planar base of cone.
What will be the efficient approach to carryout this in your view.

And regarding the "hierarchical issues" that I wrote, it was my belief looking
into the geometry that SJCLS anchors are the daughter volume of LS but we need
to place it out of LS into Acrylic vessel. That means we just can't use the
hierarchy as is but needs climbing up one level of hierarchy. I cold be wrong,
haven't gone deep into that route.

I am very new to this and still learning, appreciate your help.
Have a great day. 

Sincerely, 
Diwash


