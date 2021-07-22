G4Cerenkov_modified
=====================



Hi Miaoyu, Tao, 

I took a look at G4Cerenkov_modified photon generation 
while making some comparisons with Opticks.

I notice that doing a continue from the do-while loop 
will directly “goto" the condition "while (rand*maxSin2 > sin2Theta)”

If the continue happens on the first turn of the do-while loop
then several things will be used uninitialized.

1. cosTheta will be uninitialized
2. sin2Theta will be uninitialized
3. the second rand call will not happen so the first rand will be incorrectly re-used 

If the do-while loop completes with the unpredictable 
uninitialized values (although most likely zero) 
then the Cerenkov generation will me using the 
uninitialized values for the sin2Theta.

Simon




  for (G4int i = 0; i < fNumPhotons; i++) {
      // Determine photon energy

      G4double rand;
      G4double sampledEnergy, sampledRI;
      G4double cosTheta, sin2Theta;

      // sample an energy

      do {
         rand = G4UniformRand();
         sampledEnergy = Pmin + rand * dp;
         sampledRI = Rindex->Value(sampledEnergy);

         // check if n(E) > 1/beta
         if (sampledRI < BetaInverse) {
             continue;
         }

         cosTheta = BetaInverse / sampledRI;

         // G4cout << "TAO --> L" << __LINE__ << ": " 
         //        << " BetaInverse : " << BetaInverse
         //        << " sampledRI : " << sampledRI
         //        << " cosTheta : " << cosTheta
         //        << G4endl;

         sin2Theta = (1.0 - cosTheta)*(1.0 + cosTheta);
         rand = G4UniformRand();

        // Loop checking, 07-Aug-2015, Vladimir Ivanchenko
      } while (rand*maxSin2 > sin2Theta);


      // Generate random position of photon on cone surface 
      // defined by Theta 

      rand = G4UniformRand();

      G4double phi = twopi*rand;
      G4double sinPhi = std::sin(phi);
      G4double cosPhi = std::cos(phi);

      // calculate x,y, and z components of photon energy
      // (in coord system with primary particle direction 
      //  aligned with the z axis)

      G4double sinTheta = std::sqrt(sin2Theta);
      G4double px = sinTheta*cosPhi;
      G4double py = sinTheta*sinPhi;
