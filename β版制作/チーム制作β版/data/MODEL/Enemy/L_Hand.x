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
 200;
 -2.14300;-7.00195;-1.63140;,
 -1.96010;-7.03375;-1.60475;,
 -1.98455;-6.74440;-1.45040;,
 -2.05330;-6.53795;-1.41080;,
 -2.30685;-6.74345;-1.63375;,
 -1.83565;-7.04910;-1.60370;,
 -1.49570;-6.89930;-1.54495;,
 -1.68085;-6.68940;-1.36345;,
 -1.74905;-6.35415;-1.29365;,
 -1.45345;-6.53890;-1.52095;,
 -1.50860;-6.44985;-1.41715;,
 -1.52480;-6.23640;-1.44710;,
 -2.14505;-6.24850;-1.53995;,
 -2.38505;-6.57285;-1.62530;,
 -1.89730;-6.09175;-1.40195;,
 -1.69105;-6.11145;-1.34825;,
 -0.27790;-3.22920;-2.38700;,
 -0.17560;-3.59460;-2.30600;,
 -0.70135;-5.57320;-2.61145;,
 -0.90090;-5.58565;-2.91740;,
 -0.37055;-5.25030;-2.33965;,
 -0.65820;-5.57335;-2.36335;,
 -0.59415;-5.42060;-2.17370;,
 -0.69850;-5.54505;-2.11340;,
 -0.81975;-5.26600;-1.98645;,
 -1.21235;-5.13570;-1.82715;,
 -1.24400;-5.15550;-2.05030;,
 -1.60460;-5.09770;-1.86460;,
 -1.30450;-4.92960;-2.02420;,
 -1.78200;-5.13240;-1.94785;,
 -1.40775;-4.94395;-2.07790;,
 -1.93205;-5.18185;-2.16535;,
 -1.32755;-3.74525;-1.90950;,
 -2.00780;-5.30590;-2.54370;,
 -1.80595;-5.33440;-2.77680;,
 -1.22350;-3.41530;-2.04070;,
 -1.44965;-5.40880;-3.04935;,
 -0.91205;-3.11315;-2.07405;,
 -0.56800;-2.97355;-2.27445;,
 -1.05850;-5.45060;-3.09740;,
 -0.29695;-2.23325;-1.10990;,
 -0.46480;-2.18090;-1.18175;,
 -0.10440;-2.40325;-1.48190;,
 -0.00810;-3.00330;-1.66785;,
 0.08815;-4.30325;-1.85380;,
 -0.26060;-4.56440;-1.85380;,
 -0.63815;-4.59845;-1.85380;,
 -1.00720;-4.61335;-1.85380;,
 -1.28320;-3.43965;-1.66935;,
 -1.21450;-2.96250;-1.48400;,
 -1.02300;-2.23325;-1.10990;,
 -0.69930;-2.18090;-1.18175;,
 -1.01525;-5.82045;-1.58365;,
 -0.98845;-5.90435;-1.77155;,
 -1.05975;-6.18645;-2.01015;,
 -1.26485;-6.40160;-2.19755;,
 -1.41445;-6.41820;-2.39075;,
 -1.73950;-6.35725;-2.45135;,
 -2.02960;-6.03925;-2.50865;,
 -2.21315;-5.79085;-2.32980;,
 -2.11735;-5.50085;-2.02505;,
 -2.27610;-6.26550;-1.63900;,
 -1.63600;-5.36615;-1.74535;,
 -1.50255;-5.30345;-1.69935;,
 -1.25735;-5.47965;-1.69355;,
 -2.18135;-6.21320;1.92000;,
 -2.28040;-6.08795;1.92075;,
 -2.27520;-6.08625;-1.59935;,
 -2.16860;-6.22095;-1.59830;,
 -2.28040;-6.08795;1.92075;,
 -2.27440;-5.92845;1.92000;,
 -2.26875;-5.91465;-1.59830;,
 -2.27520;-6.08625;-1.59935;,
 -2.08470;-6.02405;2.15755;,
 -2.14945;-6.15935;2.08820;,
 0.01600;-7.40130;2.08570;,
 0.77135;-7.49175;2.15755;,
 -2.14945;-6.15935;2.08820;,
 -0.01690;-7.45405;1.91210;,
 0.01600;-7.40130;2.08570;,
 0.94740;-7.88670;1.91210;,
 0.81175;-7.97305;1.91225;,
 0.81175;-7.97305;-1.60875;,
 0.94740;-7.88670;-1.60840;,
 -0.01690;-7.45405;-1.60840;,
 0.89685;-7.85055;2.08570;,
 2.30950;-5.91235;2.08445;,
 1.94525;-5.77960;2.15755;,
 0.89685;-7.85055;2.08570;,
 2.35965;-5.95870;1.89865;,
 2.30950;-5.91235;2.08445;,
 -1.35815;-1.10265;1.11870;,
 -1.03945;-0.25580;0.95795;,
 -1.03945;-0.25585;-0.65520;,
 -1.35815;-1.10265;-0.80745;,
 -0.62170;0.03350;0.68125;,
 -0.62170;0.03350;-0.37760;,
 -1.03945;-0.25585;-0.65520;,
 -0.81985;-1.10265;1.66980;,
 -1.29880;-1.10265;1.29165;,
 -1.28430;-2.00010;1.33795;,
 -0.78350;-2.00010;1.73385;,
 -1.34680;-2.00010;1.15525;,
 -0.91945;-0.25580;1.10265;,
 0.81560;-0.25580;1.10265;,
 0.51790;0.03350;0.68125;,
 0.58210;-1.10265;1.66980;,
 1.30735;-1.10265;0.86640;,
 1.06100;-1.10265;1.29165;,
 1.00040;-2.00010;1.33965;,
 1.25850;-2.00010;0.89670;,
 0.67870;-2.00010;1.73385;,
 0.93555;-0.25580;0.95785;,
 0.93555;-0.25580;-0.65425;,
 0.51790;0.03350;-0.37760;,
 0.93555;-0.25580;0.95785;,
 1.30735;-1.10265;-0.55435;,
 0.93555;-0.25580;-0.65425;,
 -1.29880;-1.10265;-0.98035;,
 -1.30045;-2.07140;-0.84490;,
 -1.34680;-2.00010;-0.72990;,
 -1.29880;-1.10265;-0.98035;,
 -1.09670;-1.10265;-1.17670;,
 -1.12730;-2.24365;-0.88440;,
 -1.30045;-2.07140;-0.84490;,
 -0.91905;-0.25580;-0.79890;,
 0.81555;-0.25580;-0.79890;,
 0.35865;-1.10265;-1.18995;,
 -2.14375;-6.16345;-1.77895;,
 0.01600;-7.40130;-1.78200;,
 -2.08470;-6.02405;-1.85380;,
 0.77135;-7.49175;-1.85380;,
 0.89685;-7.85055;-1.78200;,
 2.30935;-5.91235;-1.78075;,
 2.35965;-5.95870;-1.59490;,
 1.94525;-5.77960;-1.85380;,
 2.17440;-4.97340;1.89525;,
 2.42220;-5.81600;1.89665;,
 2.42240;-5.81655;-1.59495;,
 2.17495;-4.97550;-1.59490;,
 2.42220;-5.81600;1.89665;,
 2.42240;-5.81655;-1.59495;,
 2.11055;-4.99750;2.08330;,
 1.56880;-3.11480;2.08220;,
 1.42315;-3.15705;2.15755;,
 1.62910;-3.09725;1.90025;,
 2.11070;-4.99885;-1.78070;,
 1.57565;-3.13480;-1.77340;,
 1.62910;-3.09725;-1.57915;,
 2.11070;-4.99885;-1.78070;,
 1.44655;-3.22530;-1.85380;,
 1.57565;-3.13480;-1.77340;,
 0.45040;-2.06760;-1.25400;,
 1.25850;-2.00010;-0.58745;,
 -1.28730;-3.99600;2.15755;,
 1.52890;-2.90285;-1.45085;,
 1.38730;-2.62835;-1.26530;,
 -1.22840;-2.96690;-1.48380;,
 -1.50415;-4.05900;1.88905;,
 -1.50415;-4.05900;-1.54740;,
 -1.42995;-3.08845;-1.24320;,
 -1.46935;-3.60405;-1.42570;,
 -1.33445;-4.24830;-1.85380;,
 1.14595;-2.56345;-1.48190;,
 1.28765;-2.84450;-1.66785;,
 -2.21715;-5.95360;2.08810;,
 -1.44060;-4.04055;2.07890;,
 -1.37035;-3.02850;-1.41410;,
 -1.37035;-3.02850;-1.41410;,
 1.06100;-1.10265;-0.98035;,
 1.00210;-2.01980;-1.03405;,
 1.06100;-1.10265;-0.98035;,
 1.00210;-2.01980;-1.03405;,
 1.30115;-2.57540;-1.42060;,
 1.30115;-2.57540;-1.42060;,
 -1.41465;-3.53155;-1.59960;,
 -1.41465;-3.53155;-1.59960;,
 1.44260;-2.85170;-1.60630;,
 1.44260;-2.85170;-1.60630;,
 -2.21450;-5.94605;-1.77895;,
 -1.45445;-4.11445;-1.76405;,
 -2.21450;-5.94605;-1.77895;,
 -1.45445;-4.11445;-1.76405;,
 -2.24300;-6.07595;2.05760;,
 -2.24300;-6.07595;2.05760;,
 0.80425;-7.93485;2.05385;,
 0.80425;-7.93485;2.05385;,
 -1.27240;-0.98565;1.25985;,
 1.03470;-0.98565;1.25980;,
 -1.27225;-0.98565;-0.94905;,
 -1.27225;-0.98565;-0.94905;,
 1.03470;-0.98565;-0.94860;,
 1.03470;-0.98565;-0.94860;,
 -2.23960;-6.07455;-1.74615;,
 -2.23960;-6.07455;-1.74615;,
 0.80425;-7.93485;-1.75020;,
 2.38005;-5.80750;2.05010;,
 2.38005;-5.80750;2.05010;,
 2.38005;-5.80800;-1.74735;,
 2.38005;-5.80800;-1.74735;;
 
 188;
 3;0,1,2;,
 4;2,3,4,0;,
 4;5,6,7,2;,
 4;7,8,3,2;,
 3;6,9,7;,
 4;10,11,8,7;,
 3;12,13,3;,
 4;14,12,3,8;,
 3;11,15,8;,
 3;1,5,2;,
 3;3,13,4;,
 3;15,14,8;,
 3;9,10,7;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;34,33,32,35;,
 4;36,34,35,37;,
 4;37,38,39,36;,
 4;38,16,19,39;,
 4;40,38,37,41;,
 4;40,42,16,38;,
 4;42,43,17,16;,
 4;44,20,17,43;,
 4;45,22,20,44;,
 4;46,24,22,45;,
 4;47,26,24,46;,
 4;47,48,28,26;,
 4;48,49,30,28;,
 4;49,50,32,30;,
 4;35,32,50,51;,
 4;37,35,51,41;,
 4;21,23,52,53;,
 4;18,21,53,54;,
 4;19,18,54,55;,
 4;39,19,55,56;,
 4;36,39,56,57;,
 4;57,58,34,36;,
 4;58,59,33,34;,
 3;60,59,61;,
 3;62,60,61;,
 4;27,29,62,63;,
 4;25,27,63,64;,
 4;23,25,64,52;,
 4;53,52,10,9;,
 4;54,53,9,6;,
 4;55,54,6,5;,
 4;56,55,5,1;,
 4;57,56,1,0;,
 4;0,4,58,57;,
 4;4,13,59,58;,
 4;61,59,13,12;,
 4;62,61,12,14;,
 4;63,62,14,15;,
 4;64,63,15,11;,
 4;52,64,11,10;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,65,78,79;,
 4;80,81,82,83;,
 4;81,78,84,82;,
 4;76,85,86,87;,
 4;88,80,89,90;,
 4;91,92,93,94;,
 4;92,95,96,97;,
 4;98,99,100,101;,
 4;99,91,102,100;,
 4;95,103,104,105;,
 4;103,98,106,104;,
 4;107,108,109,110;,
 4;108,106,111,109;,
 4;105,112,113,114;,
 4;115,107,116,117;,
 4;94,118,119,120;,
 4;121,122,123,124;,
 4;122,125,126,127;,
 4;125,96,114,126;,
 4;68,128,129,84;,
 4;128,130,131,129;,
 4;83,132,133,134;,
 4;132,131,135,133;,
 4;136,137,138,139;,
 4;140,89,134,141;,
 4;87,142,143,144;,
 4;142,136,145,143;,
 4;139,146,147,148;,
 4;149,135,150,151;,
 4;101,111,106,98;,
 3;95,114,96;,
 4;41,127,152,40;,
 4;80,83,134,89;,
 4;110,153,116,107;,
 4;120,102,91,94;,
 4;154,144,111,101;,
 3;148,155,145;,
 3;155,156,145;,
 3;156,153,145;,
 3;153,110,145;,
 4;123,50,49,157;,
 3;158,102,159;,
 3;102,120,159;,
 3;120,160,159;,
 3;160,161,159;,
 3;73,76,154;,
 3;154,76,144;,
 3;76,87,144;,
 4;136,139,148,145;,
 3;130,162,131;,
 3;162,47,131;,
 3;47,46,131;,
 3;46,45,131;,
 3;45,44,131;,
 3;44,150,131;,
 3;150,135,131;,
 4;71,70,158,159;,
 3;95,105,114;,
 4;68,84,78,65;,
 3;157,49,48;,
 3;48,47,162;,
 4;163,42,40,152;,
 4;164,43,42,163;,
 4;44,43,164,150;,
 4;70,165,166,158;,
 4;165,73,154,166;,
 4;120,119,167,160;,
 4;124,123,157,168;,
 4;127,169,170,152;,
 4;171,116,153,172;,
 4;158,166,100,102;,
 4;166,154,101,100;,
 4;144,143,109,111;,
 4;143,145,110,109;,
 4;152,170,173,163;,
 4;172,153,156,174;,
 4;160,167,175,161;,
 4;168,157,48,176;,
 4;148,147,177,155;,
 4;151,150,164,178;,
 4;130,179,180,162;,
 4;181,71,159,182;,
 4;163,173,178,164;,
 4;174,156,155,177;,
 4;162,180,176,48;,
 4;182,159,161,175;,
 4;165,70,69,183;,
 4;66,65,77,184;,
 4;74,73,165,183;,
 4;79,78,81,185;,
 4;81,80,88,185;,
 4;85,76,75,186;,
 3;103,95,92;,
 4;92,91,99,187;,
 4;99,98,103,187;,
 4;104,106,108,188;,
 4;108,107,115,188;,
 3;112,105,104;,
 4;125,122,121,189;,
 4;118,94,93,190;,
 3;97,125,189;,
 3;126,113,191;,
 4;117,116,171,192;,
 4;169,127,126,191;,
 4;72,71,181,193;,
 4;179,130,128,194;,
 4;128,68,67,194;,
 4;132,83,82,195;,
 4;82,84,129,195;,
 4;129,131,132,195;,
 4;142,87,86,196;,
 4;90,89,140,197;,
 4;137,136,142,196;,
 4;141,134,133,198;,
 4;133,135,149,198;,
 4;146,139,138,199;,
 3;126,114,113;,
 3;112,104,188;,
 3;103,92,187;,
 3;97,96,125;,
 4;122,127,41,51;,
 4;122,51,50,123;,
 4;29,31,60,62;,
 4;31,33,59,60;;
 
 MeshMaterialList {
  2;
  188;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.523922;0.294902;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  197;
  -0.096051;0.396649;-0.912931;,
  0.407814;-0.446757;0.796302;,
  -0.471922;0.314693;-0.823564;,
  0.049760;-0.282957;0.957841;,
  -0.200448;-0.418487;0.885827;,
  -0.462618;-0.098420;0.881078;,
  0.336115;-0.272313;0.901594;,
  0.016187;0.057981;0.998187;,
  -0.011645;0.599064;-0.800617;,
  -0.020799;0.644441;-0.764371;,
  0.888001;0.118723;-0.444252;,
  0.876265;0.018908;-0.481459;,
  -0.710916;0.353895;-0.607747;,
  0.716583;-0.237449;0.655841;,
  -0.313022;-0.205365;0.927277;,
  -0.208036;-0.216882;0.953773;,
  -0.041198;-0.512859;0.857484;,
  0.533442;-0.365279;0.762897;,
  0.738021;-0.301756;0.603547;,
  0.545838;-0.135584;0.826848;,
  0.377620;0.135784;0.915951;,
  0.107158;0.273729;0.955819;,
  -0.424152;0.354219;0.833441;,
  -0.634441;0.296495;0.713846;,
  -0.659271;0.081547;0.747470;,
  -0.487217;-0.287379;0.824641;,
  -0.343774;-0.393785;0.852498;,
  -0.136841;-0.475209;0.869167;,
  -0.316326;0.603350;-0.732057;,
  0.013349;0.589216;-0.807865;,
  0.592916;0.315693;-0.740803;,
  0.849859;-0.058751;-0.523724;,
  0.891550;-0.451753;-0.032518;,
  0.533500;-0.453204;0.714132;,
  0.184309;-0.262143;0.947265;,
  0.158706;0.905624;0.393265;,
  -0.154571;0.814739;0.558845;,
  -0.600671;0.601053;0.527191;,
  -0.691195;0.165565;0.703448;,
  -0.618390;0.536466;-0.574280;,
  0.760374;-0.250863;0.599082;,
  0.852254;-0.522862;0.016702;,
  0.825136;-0.431350;-0.364812;,
  0.645794;-0.335447;-0.685876;,
  -0.005458;0.003800;-0.999978;,
  -0.462423;0.196844;-0.864533;,
  -0.691527;0.157916;-0.704878;,
  -0.868492;0.329455;0.370380;,
  -0.726127;0.547775;0.415551;,
  -0.381553;0.649016;0.658176;,
  -0.023284;0.724380;0.689008;,
  0.403164;0.246438;0.881321;,
  0.818332;-0.435308;0.375286;,
  0.843349;-0.432979;0.318262;,
  0.811768;-0.583392;-0.026200;,
  0.526565;-0.725677;-0.442857;,
  0.158427;-0.725606;-0.669624;,
  -0.302920;-0.553992;-0.775456;,
  -0.671016;-0.280025;-0.686530;,
  -0.975984;0.157048;-0.150968;,
  -0.771595;0.398089;0.496152;,
  -0.522835;0.465478;0.714124;,
  -0.076775;0.419996;0.904272;,
  0.297846;0.345751;0.889800;,
  -0.938029;-0.306800;0.161169;,
  -0.636180;-0.753736;0.164794;,
  -0.512020;-0.527886;0.677623;,
  -0.284615;-0.073415;0.955827;,
  -0.756658;0.125207;0.641711;,
  -0.963148;0.219985;0.154765;,
  0.548334;-0.823643;0.144711;,
  0.681888;-0.713505;0.161059;,
  0.403772;-0.503697;0.763713;,
  -0.019284;-0.110589;0.993679;,
  -0.358009;-0.608510;0.708199;,
  -0.510355;-0.845959;0.154567;,
  -0.751296;0.610645;0.250333;,
  -0.972844;0.173848;0.152809;,
  -0.804671;0.197425;0.559936;,
  -0.320753;0.280051;0.904814;,
  -0.355334;0.667216;0.654645;,
  -0.203561;0.960688;0.188789;,
  0.762026;0.174228;0.623667;,
  0.951548;0.166155;0.258744;,
  0.742636;0.597012;0.303430;,
  0.255297;0.937453;0.236656;,
  0.371650;0.641957;0.670647;,
  0.349923;0.279581;0.894085;,
  -0.814744;0.137310;-0.563328;,
  -0.974198;0.162501;-0.156628;,
  -0.751309;0.609880;-0.252152;,
  -0.254779;0.937466;-0.237162;,
  -0.373058;0.642892;-0.668968;,
  -0.395967;0.119792;-0.910417;,
  0.743436;0.595670;-0.304107;,
  0.951803;0.166254;-0.257740;,
  0.618815;0.172833;-0.766287;,
  0.134494;0.137708;-0.981299;,
  0.306388;0.605908;-0.734167;,
  0.203582;0.960674;-0.188841;,
  -0.765538;0.124191;-0.631291;,
  -0.292893;-0.078057;-0.952954;,
  -0.528224;-0.535684;-0.658803;,
  -0.638690;-0.753815;-0.154398;,
  -0.940420;-0.307188;-0.145756;,
  -0.964021;0.220231;-0.148870;,
  0.548422;-0.823575;-0.144769;,
  -0.510884;-0.846182;-0.151569;,
  -0.360880;-0.612213;-0.703534;,
  -0.012259;-0.067194;-0.997665;,
  0.403816;-0.503522;-0.763805;,
  0.681922;-0.713452;-0.161148;,
  -0.215863;0.155710;0.963928;,
  -0.747049;0.277636;0.604017;,
  -0.953889;0.255985;0.156736;,
  0.591688;-0.289947;0.752220;,
  0.850470;-0.500117;0.163047;,
  0.984724;-0.069491;0.159656;,
  0.947137;0.279181;0.158077;,
  0.673031;0.202604;0.711323;,
  0.187782;0.015041;0.982096;,
  0.151861;0.202518;0.967432;,
  0.653692;0.427308;0.624576;,
  0.919189;0.382193;0.094972;,
  -0.986236;0.073727;-0.147997;,
  -0.723378;0.184143;-0.665444;,
  -0.519244;0.247933;-0.817872;,
  0.956628;0.226422;-0.183292;,
  0.619928;0.361263;-0.696548;,
  0.150211;0.354867;-0.922771;,
  0.589921;-0.292233;-0.752724;,
  0.190799;0.015359;-0.981509;,
  0.676276;0.203406;-0.708010;,
  0.947243;0.279648;-0.156612;,
  0.984375;-0.070952;-0.161155;,
  0.849691;-0.501288;-0.163509;,
  -0.320462;0.177009;0.930576;,
  -0.804163;0.140464;0.577574;,
  -0.989576;0.065597;0.128206;,
  0.947465;0.222526;0.229766;,
  0.729468;0.335077;0.596322;,
  0.298296;0.275936;0.913717;,
  0.865437;0.475858;-0.156775;,
  0.557770;0.644559;-0.522912;,
  0.120323;0.612158;-0.781527;,
  -0.975332;0.149191;-0.162696;,
  -0.705030;0.375002;-0.601918;,
  -0.367870;0.484759;-0.793524;,
  0.903672;0.399049;-0.155360;,
  0.637555;0.406831;-0.654226;,
  0.107570;0.189924;-0.975888;,
  -0.981463;0.173364;-0.081700;,
  -0.746728;0.251857;-0.615602;,
  -0.147144;0.132020;-0.980265;,
  0.845230;0.517378;-0.133812;,
  0.570709;0.615539;-0.543510;,
  0.123612;0.482302;-0.867240;,
  -0.977225;0.128933;-0.168545;,
  -0.796934;0.238471;-0.555003;,
  -0.800746;-0.262263;0.538538;,
  -0.368188;-0.601418;0.709037;,
  -0.740153;0.400767;0.539963;,
  0.717155;0.333994;0.611667;,
  -0.756056;0.397152;-0.520240;,
  0.637321;0.328865;-0.696900;,
  -0.819696;-0.267443;-0.506530;,
  0.548062;-0.785867;-0.286428;,
  0.662601;0.213863;0.717790;,
  0.944834;-0.075939;-0.318624;,
  -0.824404;0.435325;0.361731;,
  0.187164;0.975793;-0.113126;,
  -0.821302;0.219730;-0.526480;,
  -0.793321;0.436135;-0.424767;,
  0.889538;0.217175;-0.401943;,
  0.587275;-0.528418;0.613092;,
  -0.541646;0.465246;-0.700119;,
  -0.818469;0.361128;-0.446873;,
  0.465589;-0.660093;-0.589495;,
  -0.052960;-0.546968;-0.835477;,
  0.341216;0.333339;0.878895;,
  0.623424;-0.712214;-0.322635;,
  0.440244;-0.784375;-0.436967;,
  0.100327;-0.804577;-0.585312;,
  -0.324460;-0.670693;-0.667006;,
  -0.705755;-0.405036;-0.581253;,
  -0.809668;-0.297824;-0.505706;,
  -0.530687;-0.836745;0.135015;,
  -0.530696;-0.836731;-0.135064;,
  0.076271;0.068373;-0.994740;,
  0.000000;0.000000;-1.000000;,
  -0.026769;0.094309;-0.995183;,
  -0.259462;0.308934;-0.915008;,
  -0.046489;0.350443;-0.935429;,
  0.547902;-0.786020;0.286315;,
  -0.368106;-0.601306;-0.709175;,
  0.858066;-0.416578;0.300311;,
  0.242416;0.090920;-0.965903;;
  188;
  3;26,27,4;,
  4;4,5,25,26;,
  4;16,17,6,4;,
  4;6,7,5,4;,
  3;17,18,6;,
  4;19,20,7,6;,
  3;23,24,5;,
  4;22,23,5,7;,
  3;20,21,7;,
  3;27,16,4;,
  3;5,24,25;,
  3;21,22,7;,
  3;18,19,6;,
  4;30,31,42,43;,
  4;31,32,41,42;,
  4;32,33,40,41;,
  4;33,34,51,40;,
  4;170,35,50,170;,
  4;35,36,49,50;,
  4;36,37,48,49;,
  4;37,38,47,48;,
  4;46,171,172,39;,
  4;45,46,39,28;,
  4;28,29,44,45;,
  4;29,30,43,44;,
  4;8,29,28,0;,
  4;8,9,30,29;,
  4;173,10,31,30;,
  4;11,32,31,10;,
  4;1,33,32,174;,
  4;3,34,33,1;,
  4;15,15,34,3;,
  4;15,14,14,15;,
  4;13,13,13,13;,
  4;175,12,172,176;,
  4;39,172,12,2;,
  4;28,39,2,0;,
  4;41,40,52,53;,
  4;42,41,53,54;,
  4;43,42,54,55;,
  4;177,43,55,56;,
  4;178,44,56,57;,
  4;57,58,46,45;,
  4;58,59,171,46;,
  3;169,59,60;,
  3;61,169,60;,
  4;50,49,61,62;,
  4;51,50,62,63;,
  4;40,51,63,179;,
  4;53,52,19,18;,
  4;54,53,18,17;,
  4;55,54,180,181;,
  4;56,55,181,182;,
  4;57,56,182,183;,
  4;183,184,58,57;,
  4;184,185,59,58;,
  4;60,59,24,23;,
  4;61,60,23,22;,
  4;62,61,22,21;,
  4;63,62,21,20;,
  4;179,63,20,19;,
  4;65,64,104,103;,
  4;64,69,105,104;,
  4;67,66,74,73;,
  4;66,65,75,74;,
  4;71,70,106,111;,
  4;186,75,107,187;,
  4;73,72,115,120;,
  4;72,71,116,115;,
  4;77,76,90,89;,
  4;76,81,91,90;,
  4;79,78,137,136;,
  4;78,77,138,137;,
  4;81,80,86,85;,
  4;80,79,87,86;,
  4;83,82,140,139;,
  4;82,87,141,140;,
  4;85,84,94,99;,
  4;84,83,95,94;,
  4;89,88,125,124;,
  4;88,93,126,125;,
  4;93,92,98,97;,
  4;92,91,99,98;,
  4;103,102,108,107;,
  4;102,101,109,108;,
  4;111,110,130,135;,
  4;110,109,131,130;,
  4;118,117,134,133;,
  4;117,116,135,134;,
  4;120,119,122,121;,
  4;119,118,123,122;,
  4;133,132,149,148;,
  4;132,131,150,149;,
  4;136,141,87,79;,
  3;81,99,91;,
  4;0,97,129,8;,
  4;71,111,135,116;,
  4;139,127,95,83;,
  4;124,138,77,89;,
  4;112,121,141,136;,
  3;148,154,123;,
  3;154,142,123;,
  3;142,127,123;,
  3;127,139,123;,
  4;126,12,175,147;,
  3;114,138,151;,
  3;138,124,151;,
  3;124,145,151;,
  3;145,157,151;,
  3;67,73,112;,
  3;112,73,121;,
  3;73,120,121;,
  4;118,133,148,123;,
  3;101,153,109;,
  3;153,188,109;,
  3;188,189,109;,
  3;189,189,109;,
  3;189,190,109;,
  3;190,150,109;,
  3;150,131,109;,
  4;105,69,114,151;,
  3;81,85,99;,
  4;103,107,75,65;,
  3;147,175,191;,
  3;191,188,153;,
  4;144,9,8,129;,
  4;156,192,9,144;,
  4;190,192,156,150;,
  4;69,68,113,114;,
  4;68,67,112,113;,
  4;124,125,146,145;,
  4;125,126,147,146;,
  4;97,96,128,129;,
  4;96,95,127,128;,
  4;114,113,137,138;,
  4;113,112,136,137;,
  4;121,122,140,141;,
  4;122,123,139,140;,
  4;129,128,143,144;,
  4;128,127,142,143;,
  4;145,146,158,157;,
  4;146,147,191,158;,
  4;148,149,155,154;,
  4;149,150,156,155;,
  4;101,100,152,153;,
  4;100,105,151,152;,
  4;144,143,155,156;,
  4;143,142,154,155;,
  4;153,152,158,191;,
  4;152,151,157,158;,
  4;68,69,64,159;,
  4;64,65,66,159;,
  4;66,67,68,159;,
  4;74,75,186,160;,
  4;70,71,72,193;,
  4;72,73,74,160;,
  3;80,81,76;,
  4;76,77,78,161;,
  4;78,79,80,161;,
  4;86,87,82,162;,
  4;82,83,84,162;,
  3;84,85,86;,
  4;92,93,88,163;,
  4;88,89,90,163;,
  3;90,92,163;,
  3;98,94,164;,
  4;94,95,96,164;,
  4;96,97,98,164;,
  4;104,105,100,165;,
  4;100,101,102,165;,
  4;102,103,104,165;,
  4;110,111,106,166;,
  4;187,107,108,194;,
  4;108,109,110,194;,
  4;119,120,115,167;,
  4;115,116,117,195;,
  4;117,118,119,167;,
  4;134,135,130,168;,
  4;130,131,132,196;,
  4;132,133,134,168;,
  3;98,99,94;,
  3;84,86,162;,
  3;80,76,161;,
  3;90,91,92;,
  4;93,97,0,2;,
  4;93,2,12,126;,
  4;49,48,169,61;,
  4;48,47,59,169;;
 }
 MeshTextureCoords {
  200;
  0.500000;0.634120;,
  0.531250;0.634120;,
  0.500000;0.638750;,
  0.443820;0.638850;,
  0.440660;0.634170;,
  0.531250;0.638750;,
  0.531250;0.643380;,
  0.500000;0.643380;,
  0.446930;0.643450;,
  0.531250;0.645690;,
  0.500000;0.645690;,
  0.448460;0.645730;,
  0.426600;0.638820;,
  0.425040;0.634170;,
  0.428930;0.643430;,
  0.429710;0.645730;,
  0.545490;0.638750;,
  0.545490;0.643380;,
  0.542670;0.643380;,
  0.542670;0.638750;,
  0.545490;0.646750;,
  0.542670;0.646540;,
  0.500000;0.646750;,
  0.500000;0.646540;,
  0.449160;0.646760;,
  0.449020;0.646560;,
  0.421870;0.646760;,
  0.423420;0.646560;,
  0.420730;0.643420;,
  0.422350;0.643420;,
  0.418750;0.638810;,
  0.420300;0.638820;,
  0.416470;0.632040;,
  0.418170;0.632460;,
  0.439510;0.632460;,
  0.439220;0.632040;,
  0.500000;0.632430;,
  0.500000;0.632010;,
  0.545490;0.632010;,
  0.542670;0.632430;,
  0.562500;0.629490;,
  0.500000;0.629490;,
  0.562500;0.638750;,
  0.562500;0.643380;,
  0.562500;0.648010;,
  0.500000;0.648010;,
  0.450000;0.648010;,
  0.412500;0.648010;,
  0.410940;0.643410;,
  0.409370;0.638800;,
  0.406250;0.629490;,
  0.437500;0.629490;,
  0.500000;0.646250;,
  0.538800;0.646250;,
  0.538800;0.643380;,
  0.538800;0.638750;,
  0.538800;0.633000;,
  0.500000;0.633000;,
  0.439900;0.633040;,
  0.420500;0.633040;,
  0.421370;0.638820;,
  0.422430;0.638820;,
  0.424580;0.643430;,
  0.425550;0.646280;,
  0.448830;0.646280;,
  0.381610;0.985190;,
  0.375000;0.990560;,
  0.375000;0.760020;,
  0.382110;0.765920;,
  0.365560;-0.000000;,
  0.360200;0.009050;,
  0.140920;0.009740;,
  0.135020;-0.000000;,
  0.382200;0.009860;,
  0.379050;-0.000000;,
  0.495120;-0.000000;,
  0.499050;0.006520;,
  0.379050;1.000000;,
  0.493170;0.984700;,
  0.495120;1.000000;,
  0.509210;0.984700;,
  0.501650;0.985070;,
  0.501650;0.764910;,
  0.509210;0.765300;,
  0.493170;0.765300;,
  0.507200;-0.000000;,
  0.618980;-0.000000;,
  0.612940;0.009690;,
  0.507200;1.000000;,
  0.617430;0.983870;,
  0.618980;1.000000;,
  0.349690;0.244110;,
  0.250000;0.375000;,
  0.133710;0.258710;,
  0.150310;0.244110;,
  0.395450;0.275310;,
  0.395450;0.474690;,
  0.366290;0.491290;,
  0.395450;0.244110;,
  0.373130;0.244320;,
  0.375000;0.120510;,
  0.395580;0.120510;,
  0.349410;0.120510;,
  0.395140;0.254610;,
  0.604860;0.254610;,
  0.604550;0.275310;,
  0.604550;0.244110;,
  0.650310;0.244110;,
  0.626870;0.244310;,
  0.625000;0.120510;,
  0.650010;0.120510;,
  0.604300;0.120510;,
  0.625000;0.266370;,
  0.625000;0.483640;,
  0.604550;0.474690;,
  0.641370;0.250000;,
  0.849690;0.244110;,
  0.858640;0.250000;,
  0.125000;0.245370;,
  0.125000;0.120510;,
  0.162650;0.120510;,
  0.375000;0.504630;,
  0.395450;0.505890;,
  0.390260;0.629490;,
  0.375000;0.629490;,
  0.395190;0.495390;,
  0.604860;0.495390;,
  0.604550;0.505890;,
  0.381070;0.749320;,
  0.498800;0.750540;,
  0.382200;0.740140;,
  0.504690;0.742310;,
  0.509260;0.751110;,
  0.616000;0.749620;,
  0.617430;0.766130;,
  0.612940;0.740310;,
  0.641350;0.006170;,
  0.635600;-0.000000;,
  0.864460;-0.000000;,
  0.858870;0.006090;,
  0.625000;0.989400;,
  0.625000;0.760540;,
  0.624910;0.006830;,
  0.625000;0.101990;,
  0.609450;0.101990;,
  0.641040;0.101990;,
  0.875000;0.005140;,
  0.875000;0.101990;,
  0.857880;0.101990;,
  0.625000;0.744850;,
  0.618370;0.648010;,
  0.625000;0.648010;,
  0.616540;0.629490;,
  0.849350;0.120510;,
  0.391360;0.101990;,
  0.858100;0.105280;,
  0.858130;0.109910;,
  0.407100;0.638800;,
  0.358270;0.101990;,
  0.144100;0.101990;,
  0.150750;0.110720;,
  0.141440;0.106090;,
  0.387810;0.648010;,
  0.617320;0.638750;,
  0.617540;0.643380;,
  0.373130;0.006160;,
  0.375000;0.101990;,
  0.125000;0.111250;,
  0.375000;0.638750;,
  0.625000;0.504690;,
  0.625000;0.629490;,
  0.875000;0.245310;,
  0.875000;0.120510;,
  0.625000;0.638750;,
  0.875000;0.111250;,
  0.125000;0.106620;,
  0.375000;0.643380;,
  0.875000;0.106620;,
  0.625000;0.643380;,
  0.375000;0.744390;,
  0.375000;0.648010;,
  0.125000;0.005620;,
  0.125000;0.101990;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.500000;,
  0.125000;0.250000;,
  0.625000;0.500000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.875000;0.000000;;
 }
}
