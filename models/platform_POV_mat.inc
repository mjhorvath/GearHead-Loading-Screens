//==================================================
//POV-Ray Materials list
//==================================================
//This file has been created by PoseRay v3.12.2.456
//3D model to POV-Ray/Moray Converter.
//Author: FlyerX
//Email: flyerx_2000@yahoo.com
//Web: http://mysite.verizon.net/sfg0000/
//==================================================
//Files needed to run the POV-Ray scene:
//platform_POV_main.ini (initialization file - open this to render)
//platform_POV_scene.pov (scene setup of cameras, lights and geometry)
//platform_POV_geom.inc (geometry mesh)
//platform_POV_mat.inc (materials)
//Plat00.jpg
//Plat01.jpg
// 
 
#include "colors.inc"
 
//==================================================
//Map definitions
#declare p_map1=pigment {image_map{jpeg "platform_Plat00.jpg" interpolate 2 transmit all 0 filter all 0} }
#declare p_map2=pigment {image_map{jpeg "platform_Plat01.jpg" interpolate 2 transmit all 0 filter all 0} }

//==================================================
//Material definitions
#declare gray2_= 
material{
texture{ pigment {gamma_color_adjust(<1,1,1>*4/4)} 
        finish{specular 0.3638824 roughness 0.0843412 ambient rgb <0.00,0.00,0.00> diffuse 0.6   reflection{0 } conserve_energy}}
}
//==================================================
#declare gray3_= 
material{
texture{ pigment {gamma_color_adjust(<0.09,0.13,0.18>)} 
        finish{specular 0.8714118 roughness 0.01005236 ambient rgb <0.00,0.00,0.00> diffuse 0.6   reflection{0 } conserve_energy}}
}
//==================================================
#declare light_red_= 
material{
texture{ pigment {gamma_color_adjust(<1.00,0.00,0.00>)} 
        finish{specular 0.3 roughness 0.09632328 ambient rgb <1.00,0.00,0.00> diffuse 0.6   reflection{0 } conserve_energy}}
}
//==================================================
#declare gray1_= 
material{
texture{ pigment {gamma_color_adjust(<1,1,1>*4/4)} 
        finish{specular 0.1947451 roughness 0.0843412 ambient rgb <0.00,0.00,0.00> diffuse 0.6   reflection{0 } conserve_energy}}
}
//==================================================
#declare light_yello_= 
material{
texture{ pigment {gamma_color_adjust(<1.00,1.00,0.79>)} 
        finish{specular 0.9771373 roughness 0.09632328 ambient rgb <1.00,1.00,0.79> diffuse 0.6   reflection{0 } conserve_energy}}
}
//==================================================
