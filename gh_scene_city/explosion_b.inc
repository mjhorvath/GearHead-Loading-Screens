#declare _oldclock = -0.02;
#declare _clock = 0;
#declare _timespan = 1;
#declare Clocation = array[46] {<0.0831536,0.60337,0.130814> ,<0.0440646,2.51296,0.248955> ,<1.44973,2.91305,0.21891> ,<0.44148,3.81719,0.920288> ,<0.0132844,1.37337,-1.01001> ,<1.41988,3.53619,0.0771446> ,<1.33561,1.85386,0.0110732> ,<-0.287351,2.7805,-0.212678> ,<0.984531,5.60423,-0.975959> ,<-0.349249,1.17002,-0.754369> ,<0.241194,0.787373,0.486658> ,<2.90439,12.4978,-0.695994> ,<0.197814,0.0942394,-0.285248> ,<2.02875,10.1711,-1.8035> ,<-0.822521,1.65487,-0.203861> ,<3.38157,10.2742,0.618067> ,<2.38615,10.2625,0.0373754> ,<1.95983,9.54453,0.688353> ,<0.711534,9.70218,-0.880057> ,<0.947715,7.87705,1.93616> ,<0.673326,8.2505,-1.47944> ,<1.6611,6.71313,-0.0851256> ,<2.42451,8.00434,-0.770641> ,<0.0210233,-0.0221179,-0.267503> ,<1.43365,5.94468,1.09714> ,<0.0223018,-0.13973,-0.0618601> ,<1.93747,5.45677,-0.341218> ,<0.847351,4.31821,0.870825> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> }
#declare Olocation = array[46] {<0.0460907,0.309978,0.0814687> ,<-0.00279151,2.04901,0.237169> ,<1.33056,2.43974,0.207461> ,<0.369484,3.32535,0.874145> ,<-0.0114952,1.00452,-0.876736> ,<1.28994,3.04557,0.0725549> ,<1.16146,1.43506,0.00984582> ,<-0.3057,2.31679,-0.197183> ,<0.896053,5.09495,-0.957179> ,<-0.313187,0.824639,-0.633508> ,<0.166104,0.476829,0.355088> ,<2.80405,11.9814,-0.694426> ,<0.147574,-0.0560598,-0.220392> ,<1.93067,9.65504,-1.79726> ,<-0.778078,1.26063,-0.185136> ,<3.27749,9.75807,0.61546> ,<2.2859,9.74637,0.0372004> ,<1.86145,9.02855,0.684512> ,<0.619986,9.18636,-0.874945> ,<0.856563,7.36259,1.92107> ,<0.58433,7.73573,-1.46717> ,<1.56408,6.19936,-0.084132> ,<2.31824,7.48925,-0.762467> ,<0.00623437,-0.0423721,-0.110996> ,<1.33499,5.43411,1.0749> ,<-0.00446036,0.027946,0.012372> ,<1.82146,4.94747,-0.332172> ,<0.761105,3.81927,0.841077> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> ,<0,0,0> }
#declare Id = array[46] {55,44,45,46,51,47,50,48,39,52,54,25,53,27,49,29,30,31,32,33,34,35,36,56,40,57,42,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#declare Birth = array[46] {-0.05,-0.233333,-0.216667,-0.2,-0.116667,-0.183333,-0.133333,-0.166667,-0.316667,-0.1,-0.0666667,-0.55,-0.0833333,-0.516667,-0.15,-0.483333,-0.466667,-0.45,-0.433333,-0.416667,-0.4,-0.383333,-0.366667,-0.0333333,-0.3,-0.0166667,-0.266667,-0.25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#declare Life = array[46] {0.641737,0.435769,0.376033,0.330747,0.409703,0.619087,0.694407,0.68763,0.546127,0.711603,0.396761,0.587986,0.253297,0.539374,0.512468,0.594938,0.493694,0.560336,0.697386,0.592206,0.473545,0.743358,0.625735,0.395132,0.413921,0.581255,0.372156,0.299101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}