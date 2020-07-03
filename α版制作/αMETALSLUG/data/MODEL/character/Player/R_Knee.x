xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 228;
 3.96225;-3.05510;4.49020;,
 2.49460;-3.05510;5.89890;,
 2.49460;-4.53685;5.89890;,
 3.96225;-4.53685;4.49020;,
 0.03370;-0.04585;-2.41090;,
 -2.42720;-0.04585;-2.41090;,
 -2.42720;-0.04585;0.35905;,
 0.03370;-0.04585;0.35905;,
 0.03370;-4.53685;-5.18085;,
 -2.42720;-4.53685;-5.18085;,
 -2.42720;-3.55255;-5.84130;,
 0.03370;-3.61900;-5.85890;,
 -2.67970;-11.71255;0.36505;,
 -2.67970;-11.71255;-2.63085;,
 -0.01805;-11.71255;-2.63085;,
 -0.01805;-11.71255;0.36505;,
 5.52450;-3.44175;-2.41090;,
 5.52450;-3.44175;0.35905;,
 4.95545;-4.53685;0.35905;,
 4.95545;-4.53685;-2.41090;,
 -5.61970;-3.05510;0.35905;,
 -4.88805;-3.05510;-2.41090;,
 -4.88805;-4.53685;-2.41090;,
 -4.88805;-4.53685;0.35905;,
 3.69925;-4.53685;-3.92430;,
 2.49460;-4.53685;-5.18085;,
 2.49460;-3.05510;-5.18085;,
 3.69925;-3.05510;-4.55295;,
 -2.42720;-0.04585;3.12900;,
 0.03370;-0.04585;3.12900;,
 5.52450;-3.44175;3.12900;,
 4.95545;-4.53685;3.12900;,
 -0.01805;-11.71255;3.36090;,
 -2.67970;-11.71255;3.36090;,
 -5.51725;-3.19430;3.12900;,
 -4.88805;-4.53685;3.12900;,
 2.64350;-11.71255;3.36090;,
 2.64350;-11.71255;0.36505;,
 2.64350;-11.71255;-2.63085;,
 2.49460;-0.04585;-2.41090;,
 2.49460;-0.04585;0.35905;,
 2.49460;-0.04585;3.12900;,
 0.05860;-3.05510;6.24900;,
 0.03370;-4.53685;5.89890;,
 -3.63180;-3.55255;-4.58475;,
 -3.63180;-4.53685;-3.92430;,
 -3.89480;-4.53685;4.49020;,
 -2.42720;-4.53685;5.89890;,
 -2.42720;-3.05510;6.60620;,
 -3.89480;-3.05510;4.49020;,
 -4.10985;-6.28280;4.71640;,
 -2.56190;-6.28280;6.20225;,
 -2.83065;-5.32085;6.82900;,
 -4.53890;-5.40080;5.18380;,
 2.74940;-5.11245;6.49320;,
 0.03370;-5.23955;6.49320;,
 0.03370;-6.28280;6.20225;,
 2.62930;-6.28280;6.20225;,
 4.36900;-5.03665;4.93340;,
 4.17730;-6.28280;4.71640;,
 5.76245;-4.91870;0.35905;,
 5.46510;-4.98535;3.42610;,
 5.22490;-6.28280;3.28065;,
 5.30505;-6.21465;0.36505;,
 5.30505;-6.21465;-2.63085;,
 5.76245;-4.91870;-2.87595;,
 3.94635;-6.21465;-4.26765;,
 2.64350;-6.21465;-5.62665;,
 2.89805;-5.05275;-6.11095;,
 4.30015;-4.98710;-4.64345;,
 -0.01805;-6.21465;-5.62665;,
 0.03370;-5.18680;-6.11095;,
 -2.67970;-6.21465;-5.62665;,
 -2.83065;-5.32085;-6.11095;,
 -4.23280;-5.38645;-4.64345;,
 -3.98255;-6.21465;-4.26765;,
 -5.69500;-5.45490;0.35905;,
 -5.69500;-5.45490;-2.87595;,
 -5.34125;-6.21465;-2.63085;,
 -5.34125;-6.21465;0.36505;,
 -5.15750;-6.28280;3.28065;,
 -5.69500;-5.45490;3.59405;,
 -4.74570;-7.33265;5.41805;,
 -2.97945;-7.51530;7.14115;,
 -0.01805;-7.82160;7.14115;,
 2.94335;-8.12790;7.14115;,
 4.70950;-8.31055;5.41805;,
 5.90475;-8.43415;3.75310;,
 5.90475;-8.43415;0.36505;,
 5.90475;-8.43415;-3.02300;,
 4.39300;-8.27780;-4.87410;,
 2.94335;-8.12790;-6.41105;,
 -0.01805;-7.82160;-6.41105;,
 -2.97945;-7.51530;-6.41105;,
 -4.42915;-7.36535;-4.87410;,
 -5.94095;-7.20900;-3.02300;,
 -5.94095;-7.20900;0.36505;,
 -5.94095;-7.20900;3.75310;,
 3.94635;-6.21465;-4.26765;,
 4.39300;-8.27780;-4.87410;,
 4.30015;-4.98710;-4.64345;,
 3.69925;-3.05510;-4.55295;,
 3.69925;-4.53685;-3.92430;,
 -3.63180;-4.53685;-3.92430;,
 -3.63180;-3.55255;-4.58475;,
 -3.98255;-6.21465;-4.26765;,
 -4.23280;-5.38645;-4.64345;,
 -4.42915;-7.36535;-4.87410;,
 -2.42720;-0.64900;5.02160;,
 -2.42720;-1.46545;5.80960;,
 0.03910;-1.48910;5.74805;,
 0.03370;-0.65570;5.04250;,
 -2.42720;-2.11900;6.42880;,
 0.05400;-2.86215;6.18440;,
 -3.02245;-0.55280;-3.38055;,
 -3.47150;-1.45530;-3.87470;,
 -4.62495;-1.52155;-2.41090;,
 -3.93145;-0.58550;-2.41090;,
 -3.47150;-1.45530;-3.87470;,
 -3.63180;-2.83925;-4.27940;,
 -4.88805;-3.02755;-2.41090;,
 -4.62495;-1.52155;-2.41090;,
 -2.42720;-2.89430;-5.55950;,
 -2.42720;-1.49105;-5.03995;,
 0.03370;-1.47890;-5.05035;,
 0.03370;-2.82325;-5.52360;,
 -2.42720;-0.63650;-4.26420;,
 0.03370;-0.66065;-4.34000;,
 3.96225;-2.96740;4.49020;,
 3.78710;-1.49120;4.32780;,
 2.49460;-1.53645;5.62475;,
 2.49460;-3.05025;5.89890;,
 3.31865;-0.54145;3.89325;,
 2.49460;-0.61275;4.90775;,
 2.49460;-1.53735;-4.90535;,
 3.53945;-1.43845;-3.90260;,
 3.69925;-2.77920;-4.38705;,
 2.49460;-0.61130;-4.18510;,
 3.08775;-0.55145;-3.37860;,
 4.12760;-0.63165;0.35905;,
 4.82390;-1.47215;0.35905;,
 4.81685;-1.48175;-2.41090;,
 4.07895;-0.61420;-2.41090;,
 4.82390;-1.47215;0.35905;,
 5.28030;-2.82715;0.35905;,
 5.30185;-2.88145;-2.41090;,
 4.81685;-1.48175;-2.41090;,
 4.08805;-0.61745;3.12900;,
 -4.09655;-0.64470;0.35905;,
 -4.03770;-0.62360;3.12900;,
 -3.25245;-0.54230;3.89445;,
 -3.63180;-2.83925;-4.27940;,
 3.69925;-2.77920;-4.38705;,
 5.29845;-2.87275;3.12900;,
 -3.89480;-2.96785;4.49020;,
 -5.31760;-2.81845;3.12900;,
 -5.37055;-2.69920;0.35905;,
 -3.72005;-1.49155;4.32810;,
 -4.77920;-1.46625;3.12900;,
 -4.77920;-1.46625;3.12900;,
 4.81830;-1.48035;3.12900;,
 4.81830;-1.48035;3.12900;,
 -4.80895;-1.43975;0.35905;,
 -4.80895;-1.43975;0.35905;,
 3.53945;-1.43845;-3.90260;,
 -3.61990;-11.11745;4.23295;,
 -4.13190;-10.56535;4.71830;,
 -5.12875;-10.53390;3.39135;,
 -4.37385;-11.07305;3.36090;,
 -4.13190;-10.56535;4.71830;,
 -4.40175;-9.75775;4.99780;,
 -5.51520;-9.69310;3.47460;,
 -5.12875;-10.53390;3.39135;,
 -2.67970;-11.04310;-4.62705;,
 -2.70530;-10.52430;-5.42725;,
 -0.01805;-10.53800;-5.44660;,
 -0.01805;-11.02210;-4.68975;,
 -2.77585;-9.68400;-5.87825;,
 -0.01805;-9.75425;-5.88585;,
 3.30710;-11.12285;-3.69720;,
 3.82310;-10.57895;-4.17795;,
 5.12110;-10.54475;-2.67540;,
 4.35370;-11.06705;-2.63085;,
 3.82310;-10.57895;-4.17795;,
 4.11340;-9.79905;-4.49450;,
 5.56215;-9.73320;-2.79895;,
 5.12110;-10.54475;-2.67540;,
 2.75850;-9.71820;6.65765;,
 2.67395;-10.53280;6.17685;,
 4.11185;-10.57530;4.73675;,
 4.41270;-9.79690;5.05540;,
 2.67395;-10.53280;6.17685;,
 2.64350;-11.03660;5.37655;,
 3.59335;-11.11140;4.24185;,
 4.11185;-10.57530;4.73675;,
 4.38775;-11.05420;0.36505;,
 4.35800;-11.06535;3.36090;,
 -4.40165;-11.06255;0.36505;,
 -4.36755;-11.07545;-2.63085;,
 -3.33115;-11.13070;-3.68635;,
 2.64350;-11.03890;-4.63970;,
 -0.01805;-11.02210;5.41980;,
 -2.67970;-11.04100;5.36350;,
 -2.77525;-9.69010;6.60680;,
 -0.01805;-9.75425;6.61590;,
 5.55970;-9.74235;3.52740;,
 5.55515;-9.75980;0.36505;,
 2.75925;-9.71190;-5.92950;,
 4.11340;-9.79905;-4.49450;,
 -4.10895;-9.76210;-4.43925;,
 -4.10895;-9.76210;-4.43925;,
 -5.51640;-9.68605;-2.74535;,
 -5.51095;-9.71805;0.36505;,
 -2.70515;-10.52540;6.15860;,
 -2.70515;-10.52540;6.15860;,
 -3.84440;-10.57025;-4.15985;,
 -3.84440;-10.57025;-4.15985;,
 -5.12740;-10.53265;-2.66150;,
 -5.12740;-10.53265;-2.66150;,
 2.67415;-10.53175;-5.44545;,
 5.12845;-10.54860;0.36505;,
 5.12845;-10.54860;0.36505;,
 -0.01805;-10.53800;6.17670;,
 -0.01805;-10.53800;6.17670;,
 5.12155;-10.54675;3.40500;,
 5.12155;-10.54675;3.40500;,
 -5.13520;-10.53790;0.36505;,
 -5.13520;-10.53790;0.36505;;
 
 200;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;6,28,29,7;,
 4;17,30,31,18;,
 4;32,33,12,15;,
 4;34,20,23,35;,
 4;36,32,15,37;,
 4;14,38,37,15;,
 4;25,8,11,26;,
 4;39,4,7,40;,
 4;29,41,40,7;,
 4;1,42,43,2;,
 4;44,10,9,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,54,57,59;,
 4;60,61,62,63;,
 4;64,65,60,63;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 4;74,73,72,75;,
 4;76,77,78,79;,
 4;80,81,76,79;,
 4;82,83,51,50;,
 4;57,56,84,85;,
 4;59,57,85,86;,
 4;62,87,88,63;,
 4;88,89,64,63;,
 4;90,91,67,66;,
 4;91,92,70,67;,
 4;92,93,72,70;,
 4;75,72,93,94;,
 4;78,95,96,79;,
 4;96,97,80,79;,
 4;98,64,89,99;,
 4;100,65,64,98;,
 4;101,16,19,102;,
 4;103,22,21,104;,
 4;105,78,77,106;,
 4;107,95,78,105;,
 4;3,31,30,0;,
 4;59,62,61,58;,
 4;86,87,62,59;,
 4;50,80,97,82;,
 4;53,81,80,50;,
 4;49,34,35,46;,
 4;53,52,47,46;,
 4;46,35,81,53;,
 4;76,81,35,23;,
 4;22,77,76,23;,
 4;106,77,22,103;,
 4;45,9,73,74;,
 4;71,73,9,8;,
 4;68,71,8,25;,
 4;69,68,25,24;,
 4;102,19,65,100;,
 4;60,65,19,18;,
 4;31,61,60,18;,
 4;58,61,31,3;,
 4;3,2,54,58;,
 4;2,43,55,54;,
 4;43,42,48,47;,
 4;55,43,47,52;,
 4;56,55,52,51;,
 4;84,56,51,83;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;123,126,127,124;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;26,134,135,136;,
 4;134,137,138,135;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;142,39,40,139;,
 4;139,40,41,147;,
 4;148,6,5,117;,
 4;149,28,6,148;,
 3;137,39,138;,
 4;127,4,39,137;,
 4;126,5,4,127;,
 3;117,5,114;,
 3;150,108,28;,
 4;29,28,108,111;,
 4;133,41,29,111;,
 3;147,41,132;,
 3;138,39,142;,
 3;114,5,126;,
 3;150,28,149;,
 3;132,41,133;,
 4;151,122,10,44;,
 4;11,10,122,125;,
 3;26,11,125;,
 3;27,26,136;,
 4;145,16,101,152;,
 4;144,17,16,145;,
 4;153,30,17,144;,
 4;0,30,153,128;,
 4;131,1,0,128;,
 4;113,42,1,131;,
 4;49,48,112,154;,
 4;155,34,49,154;,
 4;156,20,34,155;,
 4;120,21,20,156;,
 4;104,21,120,119;,
 4;112,48,42,113;,
 4;150,157,109,108;,
 4;157,154,112,109;,
 4;151,115,123,122;,
 4;115,114,126,123;,
 4;154,157,158,155;,
 4;157,150,149,159;,
 4;132,129,160,147;,
 4;129,128,153,161;,
 4;125,124,134,26;,
 4;124,127,137,134;,
 4;111,110,130,133;,
 4;110,113,131,130;,
 4;155,158,162,156;,
 4;159,149,148,163;,
 4;156,162,121,120;,
 4;163,148,117,116;,
 4;147,160,140,139;,
 4;161,153,144,143;,
 4;142,141,135,138;,
 4;146,145,152,164;,
 4;165,166,167,168;,
 4;169,170,171,172;,
 4;173,174,175,176;,
 4;174,177,178,175;,
 4;179,180,181,182;,
 4;183,184,185,186;,
 4;187,188,189,190;,
 4;191,192,193,194;,
 4;195,37,38,182;,
 4;196,36,37,195;,
 4;197,12,33,168;,
 4;198,13,12,197;,
 3;199,13,198;,
 4;14,13,173,176;,
 4;200,38,14,176;,
 3;179,38,200;,
 3;193,36,196;,
 4;201,32,36,192;,
 4;202,33,32,201;,
 3;165,33,202;,
 4;170,203,83,82;,
 4;85,84,204,187;,
 4;86,85,187,190;,
 4;190,205,87,86;,
 4;88,87,205,206;,
 4;185,89,88,206;,
 4;99,89,185,184;,
 4;207,91,90,208;,
 4;178,92,91,207;,
 4;177,93,92,178;,
 4;94,93,177,209;,
 4;210,211,95,107;,
 4;96,95,211,212;,
 4;171,97,96,212;,
 4;82,97,171,170;,
 3;199,173,13;,
 3;182,38,179;,
 3;168,33,165;,
 3;192,36,193;,
 4;204,84,83,203;,
 4;170,169,213,203;,
 4;166,165,202,214;,
 4;199,215,174,173;,
 4;215,209,177,174;,
 4;210,216,217,211;,
 4;215,199,198,218;,
 4;208,180,219,207;,
 4;180,179,200,219;,
 4;182,181,220,195;,
 4;186,185,206,221;,
 4;203,213,222,204;,
 4;214,202,201,223;,
 4;204,222,188,187;,
 4;223,201,192,191;,
 4;176,175,219,200;,
 4;175,178,207,219;,
 4;195,220,224,196;,
 4;221,206,205,225;,
 4;211,217,226,212;,
 4;218,198,197,227;,
 4;212,226,172,171;,
 4;227,197,168,167;,
 4;196,224,194,193;,
 4;225,205,190,189;;
 
 MeshMaterialList {
  1;
  200;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  210;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.179481;-0.983761;0.000003;,
  0.171363;0.985208;-0.000001;,
  -0.179491;-0.983760;0.000001;,
  -0.171369;0.985207;-0.000001;,
  -0.708125;0.338299;0.619768;,
  -0.467568;0.518528;0.715898;,
  0.348853;0.382873;0.855401;,
  0.663259;0.387544;0.640232;,
  0.887350;-0.461096;-0.000000;,
  0.657526;-0.236540;-0.715338;,
  0.378139;-0.237374;-0.894799;,
  0.066113;-0.451552;-0.889792;,
  -0.354314;-0.531001;-0.769740;,
  -0.751414;-0.287840;-0.593739;,
  -0.941971;-0.330772;-0.057280;,
  -0.607430;-0.580660;0.542091;,
  -0.270524;-0.518823;0.810950;,
  0.388304;0.118867;0.913833;,
  0.757921;0.087775;0.646414;,
  0.999731;-0.013997;0.018493;,
  0.753793;-0.027119;-0.656552;,
  0.408738;-0.012138;-0.912571;,
  0.018423;0.007725;-0.999801;,
  -0.334254;-0.485418;-0.807864;,
  -0.737112;0.043567;-0.674365;,
  -0.998307;0.055807;0.016424;,
  -0.206565;-0.960633;-0.185782;,
  -0.000002;-0.986942;-0.161077;,
  0.206553;-0.960642;-0.185750;,
  0.942867;-0.035730;-0.331247;,
  0.847162;-0.416200;-0.330294;,
  0.197495;0.964088;-0.177569;,
  0.000000;0.988125;-0.153651;,
  -0.197511;0.964085;-0.177566;,
  -0.900215;0.295736;-0.319614;,
  -0.939209;0.054354;-0.339017;,
  -0.193408;0.966154;0.170706;,
  0.000002;0.988125;0.153652;,
  0.193380;0.966162;0.170691;,
  0.866060;-0.333770;0.372207;,
  0.945909;0.046962;0.321015;,
  0.202357;-0.962872;0.178686;,
  0.000001;-0.986942;0.161076;,
  -0.202366;-0.962870;0.178690;,
  -0.789088;-0.555517;0.262185;,
  -0.874833;-0.311896;0.370658;,
  -0.783126;-0.044381;-0.620277;,
  -0.406227;-0.096583;-0.908653;,
  0.082324;-0.032522;-0.996075;,
  0.355867;0.159081;-0.920897;,
  0.659550;0.086668;-0.746648;,
  0.938083;-0.027285;-0.345336;,
  0.998724;-0.050493;-0.000003;,
  0.917879;-0.031939;0.395572;,
  0.702127;-0.005117;0.712034;,
  0.423565;0.011898;0.905788;,
  -0.400927;-0.046656;0.914921;,
  -0.748220;-0.013893;0.663305;,
  -0.906127;0.032406;0.421763;,
  -0.995539;0.043426;-0.083760;,
  -0.925815;0.009842;-0.377850;,
  -0.891184;-0.453488;0.011848;,
  -0.829402;-0.472982;-0.297287;,
  -0.654747;-0.468686;-0.592993;,
  0.010085;-0.428745;-0.903369;,
  0.362508;-0.430533;-0.826577;,
  0.692802;-0.386326;-0.608915;,
  0.874630;-0.373265;-0.309347;,
  0.954142;-0.298106;0.027306;,
  0.912049;-0.248829;0.325963;,
  0.736580;-0.225792;0.637548;,
  0.365982;-0.262566;0.892814;,
  -0.726625;0.253488;0.638561;,
  -0.353683;0.216750;0.909905;,
  0.378143;0.096893;0.920663;,
  0.755390;0.051264;0.653267;,
  0.950810;0.027444;0.308556;,
  0.999957;0.008274;0.004229;,
  0.941998;0.008943;-0.335500;,
  0.748368;0.023526;-0.662867;,
  0.395757;0.057605;-0.916547;,
  0.002288;0.095945;-0.995384;,
  -0.383395;0.153809;-0.910687;,
  -0.734240;0.178377;-0.655037;,
  -0.922653;0.200409;-0.329465;,
  -0.978775;0.204745;0.008893;,
  -0.917939;0.257701;0.301626;,
  0.107466;-0.008990;0.994168;,
  0.041612;0.265844;0.963117;,
  0.021904;0.212926;0.976823;,
  0.032649;0.109078;0.993497;,
  0.004608;0.142108;0.989841;,
  -0.486687;0.762964;0.425467;,
  -0.696408;0.405063;0.592401;,
  -0.748757;0.181509;0.637508;,
  -0.203609;0.397124;0.894894;,
  -0.364732;0.558612;0.744932;,
  -0.245268;0.828307;0.503737;,
  -0.760787;0.216265;-0.611909;,
  -0.707849;0.399786;-0.582342;,
  -0.495079;0.759058;-0.422762;,
  -0.254477;0.826186;-0.502652;,
  -0.369421;0.496392;-0.785572;,
  -0.377215;0.344265;-0.859762;,
  -0.538017;0.814762;0.216102;,
  -0.801613;0.488049;0.345290;,
  -0.847516;0.348069;0.400705;,
  0.483678;0.758002;0.437595;,
  0.675806;0.360663;0.642813;,
  0.701500;0.119713;0.702543;,
  0.546741;0.809757;0.212997;,
  0.823080;0.461065;0.331599;,
  0.887138;0.276091;0.369811;,
  0.068542;0.343585;-0.936617;,
  0.036941;0.483798;-0.874400;,
  0.009714;0.833095;-0.553044;,
  0.253536;0.816476;-0.518735;,
  0.355611;0.449216;-0.819601;,
  0.013560;0.833416;0.552479;,
  0.063542;0.521833;0.850678;,
  0.121347;0.293041;0.948368;,
  0.426811;0.144528;0.892717;,
  0.389648;0.415761;0.821777;,
  0.252695;0.811793;0.526438;,
  -0.568675;0.822499;-0.010224;,
  -0.863611;0.502757;-0.037579;,
  -0.922624;0.378097;-0.076204;,
  -0.551199;0.802920;-0.226935;,
  -0.831844;0.440957;-0.337036;,
  -0.895772;0.230351;-0.380172;,
  0.938158;0.346208;-0.000072;,
  0.871140;0.491035;-0.000380;,
  0.571847;0.820360;-0.000316;,
  0.539476;0.813383;-0.217656;,
  0.816339;0.488514;-0.308132;,
  0.885881;0.341993;-0.313457;,
  0.631219;0.335723;-0.699180;,
  0.644382;0.424397;-0.636128;,
  0.474739;0.765017;-0.435170;,
  -0.720726;-0.318860;0.615534;,
  -0.599418;-0.610950;0.517144;,
  -0.401882;-0.846675;0.348757;,
  -0.192634;-0.889685;0.413948;,
  -0.296457;-0.674796;0.675843;,
  -0.362330;-0.370156;0.855396;,
  -0.715410;-0.314223;-0.624061;,
  -0.600458;-0.600746;-0.527782;,
  -0.410085;-0.836563;-0.363307;,
  -0.380743;-0.370290;-0.847301;,
  -0.314600;-0.673798;-0.668598;,
  -0.207190;-0.887908;-0.410722;,
  -0.452020;-0.873339;-0.181540;,
  -0.718093;-0.641837;-0.269051;,
  -0.892840;-0.318804;-0.318122;,
  0.686638;-0.379617;-0.620015;,
  0.577574;-0.633243;-0.515181;,
  0.402226;-0.842582;-0.358149;,
  0.442645;-0.878816;-0.178180;,
  0.688692;-0.676697;-0.260354;,
  0.862590;-0.396232;-0.314546;,
  -0.000925;-0.902114;0.431497;,
  -0.004499;-0.686735;0.726894;,
  -0.012924;-0.379412;0.925138;,
  0.187822;-0.892733;0.409575;,
  0.280268;-0.694009;0.663175;,
  0.333008;-0.412265;0.848023;,
  -0.000913;-0.902124;-0.431476;,
  -0.004483;-0.686792;-0.726840;,
  -0.012937;-0.379452;-0.925121;,
  0.352058;-0.411151;-0.840839;,
  0.298450;-0.692338;-0.656960;,
  0.202290;-0.890831;-0.406815;,
  0.461291;-0.887249;-0.000119;,
  0.741828;-0.670590;-0.000271;,
  0.929579;-0.368622;-0.000142;,
  0.445674;-0.881114;0.158156;,
  0.696499;-0.677740;0.235707;,
  0.872580;-0.395446;0.286751;,
  -0.471264;-0.881992;-0.000146;,
  -0.771038;-0.636790;-0.000303;,
  -0.955321;-0.295570;-0.000148;,
  -0.455533;-0.875482;0.161307;,
  -0.726800;-0.642099;0.243867;,
  -0.902947;-0.317116;0.290042;,
  0.690591;-0.387336;0.610782;,
  0.575123;-0.644708;0.503573;,
  0.393618;-0.852794;0.343230;,
  -0.253591;0.632386;0.731970;,
  -0.547767;0.666940;0.505116;,
  -0.307734;0.532572;-0.788458;,
  -0.716865;0.652444;0.245808;,
  -0.517086;0.737858;0.433805;,
  -0.227736;0.756346;0.613251;,
  -0.675762;0.707955;0.205294;,
  -0.751092;0.660197;0.000000;,
  -0.665120;0.712582;-0.223253;,
  -0.513039;0.736423;-0.440991;,
  -0.260329;0.798102;-0.543381;,
  -0.019201;0.820920;-0.570720;,
  0.152320;0.885305;-0.439356;,
  0.312929;0.901703;-0.298342;,
  0.371426;0.918242;-0.137387;,
  0.482134;0.875876;0.019722;,
  0.525004;0.824442;0.211344;,
  0.475752;0.766071;0.432198;,
  0.224826;0.740997;0.632753;,
  0.064802;-0.331132;0.941357;,
  -0.819459;0.054050;0.570583;;
  200;
  4;56,57,8,9;,
  4;34,35,5,0;,
  4;13,14,49,50;,
  4;4,28,29,1;,
  4;53,54,10,32;,
  4;61,62,36,16;,
  4;11,12,51,52;,
  4;5,38,39,0;,
  4;54,55,41,10;,
  4;44,45,4,1;,
  4;60,61,16,47;,
  4;43,44,1,2;,
  4;29,30,2,1;,
  4;12,13,50,51;,
  4;33,34,0,3;,
  4;39,40,3,0;,
  4;57,89,90,8;,
  4;48,49,14,15;,
  4;6,7,58,59;,
  4;17,18,18,17;,
  4;73,91,92,19;,
  4;72,73,19,20;,
  4;70,71,42,21;,
  4;31,69,70,21;,
  4;22,23,67,68;,
  4;23,24,66,67;,
  4;24,25,25,66;,
  4;65,25,25,26;,
  4;63,64,37,27;,
  4;46,46,63,27;,
  4;74,75,189,190;,
  4;19,92,93,76;,
  4;20,19,76,77;,
  4;42,78,79,21;,
  4;79,80,31,21;,
  4;81,82,23,22;,
  4;82,83,24,23;,
  4;83,84,191,24;,
  4;26,191,84,85;,
  4;37,86,87,27;,
  4;87,88,192,27;,
  4;22,31,80,81;,
  4;68,69,31,22;,
  4;52,53,32,11;,
  4;15,36,62,48;,
  4;26,37,64,65;,
  4;85,86,37,26;,
  4;9,41,55,56;,
  4;20,42,71,72;,
  4;77,78,42,20;,
  4;190,192,88,74;,
  4;17,46,46,17;,
  4;59,60,47,6;,
  4;193,194,7,6;,
  4;6,195,195,193;,
  4;196,195,195,196;,
  4;36,197,196,196;,
  4;198,197,36,198;,
  4;198,199,199,198;,
  4;200,199,199,200;,
  4;201,200,200,201;,
  4;202,201,201,202;,
  4;202,203,203,202;,
  4;204,203,203,204;,
  4;205,205,204,204;,
  4;206,205,205,9;,
  4;9,8,207,206;,
  4;8,90,91,207;,
  4;90,89,58,208;,
  4;91,90,7,194;,
  4;92,91,18,18;,
  4;93,92,189,75;,
  4;99,98,121,120;,
  4;98,97,122,121;,
  4;102,101,130,129;,
  4;101,100,131,130;,
  4;105,104,116,115;,
  4;104,103,117,116;,
  4;111,110,124,123;,
  4;110,109,125,124;,
  4;51,119,139,138;,
  4;119,118,140,139;,
  4;134,133,136,135;,
  4;133,132,137,136;,
  4;135,33,3,134;,
  4;134,3,40,112;,
  4;126,5,35,129;,
  4;106,38,5,126;,
  3;118,33,140;,
  4;117,34,33,118;,
  4;103,35,34,117;,
  3;129,35,102;,
  3;94,99,38;,
  4;39,38,99,120;,
  4;125,40,39,120;,
  3;112,40,109;,
  3;140,33,135;,
  3;102,35,103;,
  3;94,38,106;,
  3;109,40,125;,
  4;100,105,49,48;,
  4;50,49,105,115;,
  3;51,50,115;,
  3;52,51,138;,
  4;137,53,52,138;,
  4;132,54,53,137;,
  4;114,55,54,132;,
  4;56,55,114,111;,
  4;123,57,56,111;,
  4;122,89,57,123;,
  4;59,58,209,96;,
  4;108,60,59,96;,
  4;128,61,60,108;,
  4;131,62,61,128;,
  4;48,62,131,100;,
  4;97,58,89,122;,
  4;94,95,98,99;,
  4;95,96,97,98;,
  4;100,101,104,105;,
  4;101,102,103,104;,
  4;96,95,107,108;,
  4;95,94,106,107;,
  4;109,110,113,112;,
  4;110,111,114,113;,
  4;115,116,119,51;,
  4;116,117,118,119;,
  4;120,121,124,125;,
  4;121,122,123,124;,
  4;108,107,127,128;,
  4;107,106,126,127;,
  4;128,127,130,131;,
  4;127,126,129,130;,
  4;112,113,133,134;,
  4;113,114,132,133;,
  4;135,136,139,140;,
  4;136,137,138,139;,
  4;143,142,184,183;,
  4;142,141,185,184;,
  4;152,151,169,168;,
  4;151,150,170,169;,
  4;158,157,160,159;,
  4;157,156,161,160;,
  4;167,166,187,186;,
  4;166,165,188,187;,
  4;174,2,30,159;,
  4;177,43,2,174;,
  4;180,4,45,183;,
  4;153,28,4,180;,
  3;149,28,153;,
  4;29,28,152,168;,
  4;173,30,29,168;,
  3;158,30,173;,
  3;188,43,177;,
  4;162,44,43,165;,
  4;144,45,44,162;,
  3;143,45,144;,
  4;141,146,75,74;,
  4;76,93,164,167;,
  4;77,76,167,186;,
  4;186,179,78,77;,
  4;79,78,179,176;,
  4;161,80,79,176;,
  4;81,80,161,156;,
  4;171,82,81,156;,
  4;170,83,82,171;,
  4;150,84,83,170;,
  4;85,84,150,147;,
  4;147,155,86,85;,
  4;87,86,155,182;,
  4;185,88,87,182;,
  4;74,88,185,141;,
  3;149,152,28;,
  3;159,30,158;,
  3;183,45,143;,
  3;165,43,188;,
  4;164,93,75,146;,
  4;141,142,145,146;,
  4;142,143,144,145;,
  4;149,148,151,152;,
  4;148,147,150,151;,
  4;147,148,154,155;,
  4;148,149,153,154;,
  4;156,157,172,171;,
  4;157,158,173,172;,
  4;159,160,175,174;,
  4;160,161,176,175;,
  4;146,145,163,164;,
  4;145,144,162,163;,
  4;164,163,166,167;,
  4;163,162,165,166;,
  4;168,169,172,173;,
  4;169,170,171,172;,
  4;174,175,178,177;,
  4;175,176,179,178;,
  4;155,154,181,182;,
  4;154,153,180,181;,
  4;182,181,184,185;,
  4;181,180,183,184;,
  4;177,178,187,188;,
  4;178,179,186,187;;
 }
 MeshTextureCoords {
  228;
  0.625000;0.218980;,
  0.562500;0.218980;,
  0.562500;0.175000;,
  0.625000;0.175000;,
  0.500000;0.437500;,
  0.437500;0.437500;,
  0.437500;0.375000;,
  0.500000;0.375000;,
  0.500000;0.575000;,
  0.437500;0.575000;,
  0.437500;0.531020;,
  0.500000;0.531020;,
  0.437500;0.875000;,
  0.437500;0.812500;,
  0.500000;0.812500;,
  0.500000;0.875000;,
  0.812500;0.218980;,
  0.750000;0.218980;,
  0.750000;0.175000;,
  0.812500;0.175000;,
  0.250000;0.218980;,
  0.187500;0.218980;,
  0.187500;0.175000;,
  0.250000;0.175000;,
  0.625000;0.575000;,
  0.562500;0.575000;,
  0.562500;0.531020;,
  0.625000;0.531020;,
  0.437500;0.312500;,
  0.500000;0.312500;,
  0.687500;0.218980;,
  0.687500;0.175000;,
  0.500000;0.937500;,
  0.437500;0.937500;,
  0.312500;0.218980;,
  0.312500;0.175000;,
  0.562500;0.937500;,
  0.562500;0.875000;,
  0.562500;0.812500;,
  0.562500;0.437500;,
  0.562500;0.375000;,
  0.562500;0.312500;,
  0.500630;0.218980;,
  0.500000;0.175000;,
  0.375000;0.531020;,
  0.375000;0.575000;,
  0.375000;0.175000;,
  0.437500;0.175000;,
  0.437500;0.218980;,
  0.375000;0.218980;,
  0.375000;0.105000;,
  0.437500;0.105000;,
  0.437500;0.138860;,
  0.375000;0.138860;,
  0.562500;0.138860;,
  0.500000;0.138860;,
  0.500000;0.105000;,
  0.562500;0.105000;,
  0.625000;0.138860;,
  0.625000;0.105000;,
  0.750000;0.138860;,
  0.687500;0.138860;,
  0.687500;0.105000;,
  0.750000;0.105000;,
  0.812500;0.105000;,
  0.812500;0.138860;,
  0.625000;0.645000;,
  0.562500;0.645000;,
  0.562500;0.611140;,
  0.625000;0.611140;,
  0.500000;0.645000;,
  0.500000;0.611140;,
  0.437500;0.645000;,
  0.437500;0.611140;,
  0.375000;0.611140;,
  0.375000;0.645000;,
  0.250000;0.138860;,
  0.187500;0.138860;,
  0.187500;0.105000;,
  0.250000;0.105000;,
  0.312500;0.105000;,
  0.312500;0.138860;,
  0.375000;0.057020;,
  0.437500;0.057020;,
  0.500000;0.057020;,
  0.562500;0.057020;,
  0.625000;0.057020;,
  0.687500;0.057020;,
  0.750000;0.057020;,
  0.812500;0.057020;,
  0.625000;0.692980;,
  0.562500;0.692980;,
  0.500000;0.692980;,
  0.437500;0.692980;,
  0.375000;0.692980;,
  0.187500;0.057020;,
  0.250000;0.057020;,
  0.312500;0.057020;,
  0.875000;0.105000;,
  0.875000;0.057020;,
  0.875000;0.138860;,
  0.875000;0.218980;,
  0.875000;0.175000;,
  0.125000;0.175000;,
  0.125000;0.218980;,
  0.125000;0.105000;,
  0.125000;0.138860;,
  0.125000;0.057020;,
  0.437500;0.269800;,
  0.437500;0.250000;,
  0.500000;0.250000;,
  0.500000;0.269320;,
  0.437500;0.226760;,
  0.500510;0.224700;,
  0.406610;0.473390;,
  0.375000;0.500000;,
  0.375000;0.437500;,
  0.399300;0.437500;,
  0.125000;0.250000;,
  0.125000;0.233320;,
  0.187500;0.219800;,
  0.187500;0.250000;,
  0.437500;0.517790;,
  0.437500;0.500000;,
  0.500000;0.500000;,
  0.500000;0.515680;,
  0.437500;0.479320;,
  0.500000;0.481030;,
  0.625000;0.221580;,
  0.625000;0.250000;,
  0.562500;0.250000;,
  0.562500;0.219120;,
  0.597590;0.277410;,
  0.562500;0.272360;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.625000;0.522830;,
  0.562500;0.477530;,
  0.593270;0.473290;,
  0.603980;0.375000;,
  0.625000;0.375000;,
  0.625000;0.437500;,
  0.602740;0.437500;,
  0.750000;0.250000;,
  0.750000;0.232290;,
  0.812500;0.231120;,
  0.812500;0.250000;,
  0.602970;0.312500;,
  0.395100;0.375000;,
  0.396600;0.312500;,
  0.402350;0.277350;,
  0.375000;0.516680;,
  0.875000;0.227170;,
  0.687500;0.231310;,
  0.375000;0.221570;,
  0.312500;0.228820;,
  0.250000;0.229540;,
  0.375000;0.250000;,
  0.312500;0.250000;,
  0.375000;0.312500;,
  0.625000;0.312500;,
  0.687500;0.250000;,
  0.250000;0.250000;,
  0.375000;0.375000;,
  0.875000;0.250000;,
  0.400480;0.974520;,
  0.375000;1.000000;,
  0.375000;0.937500;,
  0.397720;0.937500;,
  0.375000;0.000000;,
  0.375000;0.016050;,
  0.312500;0.016540;,
  0.312500;0.000000;,
  0.437500;0.770850;,
  0.437500;0.750000;,
  0.500000;0.750000;,
  0.500000;0.769550;,
  0.437500;0.731720;,
  0.500000;0.731160;,
  0.594330;0.775810;,
  0.625000;0.750000;,
  0.625000;0.812500;,
  0.602660;0.812500;,
  0.875000;0.000000;,
  0.875000;0.021320;,
  0.812500;0.024440;,
  0.812500;0.000000;,
  0.562500;0.021870;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.625000;0.021670;,
  0.562500;1.000000;,
  0.562500;0.979550;,
  0.599900;0.974900;,
  0.625000;1.000000;,
  0.603460;0.875000;,
  0.602760;0.937500;,
  0.397060;0.875000;,
  0.397860;0.812500;,
  0.406250;0.776300;,
  0.562500;0.770590;,
  0.500000;0.980450;,
  0.437500;0.979280;,
  0.437500;0.018180;,
  0.500000;0.018840;,
  0.687500;0.024210;,
  0.750000;0.023770;,
  0.562500;0.727990;,
  0.625000;0.728680;,
  0.375000;0.733870;,
  0.125000;0.016130;,
  0.187500;0.016650;,
  0.250000;0.016130;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.375000;0.750000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.812500;,
  0.562500;0.750000;,
  0.625000;0.875000;,
  0.750000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.937500;,
  0.687500;0.000000;,
  0.250000;0.000000;,
  0.375000;0.875000;;
 }
}
