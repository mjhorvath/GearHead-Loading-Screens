 #declare S = 10;  
     
 global_settings { 
   max_trace_level 2   
   ambient_light <0.5,0.5,0.8>
 }
 
 #include "colors.inc"   
 #include "metals.inc"
 #include "golds.inc"
 #include "finish.inc"  
 #include "textures.inc"
 
 #declare P_Brass6    = color rgb <1, 0.50, 0.05>;       
 #declare T_Brass_6A = texture { pigment { P_Brass6 } finish { F_MetalA  } }      
 
 camera {
        location <15,15,6>
        direction z*1.2
        look_at <0,0,0>
 }
 
 plane {y, 0
        texture{pigment{ P_Silver2*0.5}}
 }
 #declare C = 5.8;    
 difference{  
   merge{
     box {<-5.3,0.4,-5.2> <5.3,4,5.2>}
     box {<-5.4,0,-5.3> <5.4,0.44,5.3>}        
 #declare NrX = -C;    
 #while (NrX < -4)
     cylinder {<NrX,0,-NrX> <NrX,0.4,-NrX>,0.8}     
 
  #declare NrX = NrX + 0.05;  //next Nr
 
 #end  
 #declare NrX = C;    
 #while (NrX > 4)
     cylinder {<NrX,0,-NrX> <NrX,0.4,-NrX>,0.8}     
 
  #declare NrX = NrX - 0.05;  //next Nr
 
 #end   
 
 #declare NrX = -5;    
 #declare Q = 0.4;  
 #while (NrX < 5.2)
     cylinder {<-5.3,4/Q,NrX> <5.3,4/Q,NrX>,0.2 transform{scale <1,Q,1>}}     
 
  #declare NrX = NrX + 1;  //next Nr
 
 #end       
      
   }    
   union{  
 
 #declare NrX = -4.5;
 #while (NrX < 4.5+1)
   box {<NrX-0.2,0.9,-6> <NrX+0.2,5,6>}     
 
  #declare NrX = NrX + 1;  //next Nr
 
 #end  
 #declare NrX = -4.5;  
 #while (NrX < 4.5+1)
   box {<-6,1,NrX-0.3> <6,5,NrX+0.3>}     
 
  #declare NrX = NrX + 1;  //next Nr
 
 #end   
 cylinder {<C,-1,-C> <C,1,-C>,0.4}
 cylinder {<-C,-1,C> <-C,1,C>,0.4}                      
   }
   texture{T_Brass_6A}
 }
           
 light_source {<100,200,-100> color <1.2 1.1 0.9> area_light  <200,0,0> <0,0,200> S S circular} 
 light_source {<500,200,-100> color <1.2 1.1 0.9> area_light  <1000,0,0> <0,50,2000> S S circular}
 light_source {<0,50,0> White*2 area_light  <30,0,0> <0,0,30> S S circular}
