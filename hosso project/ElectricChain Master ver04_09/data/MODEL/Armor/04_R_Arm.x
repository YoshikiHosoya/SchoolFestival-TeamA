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
 201;
 -3.43796;-1.11175;-3.47757;,
 -0.44883;-0.09131;-4.53969;,
 -0.66722;-2.22384;-4.83554;,
 -4.41577;-1.53902;-0.95700;,
 -3.34818;1.18448;-0.56823;,
 -2.78034;0.73868;-3.23653;,
 -3.43796;-1.11175;-3.47757;,
 -3.21330;-1.49911;2.42827;,
 -3.34818;1.18448;-0.56823;,
 -4.41577;-1.53902;-0.95700;,
 -4.11762;-3.29708;1.02451;,
 -1.53696;-0.67754;4.40071;,
 -3.21330;-1.49911;2.42827;,
 -0.59200;-2.93025;4.14479;,
 -4.11762;-3.29708;1.02451;,
 -1.26467;-4.74259;2.82311;,
 -1.53696;-0.67754;4.40071;,
 -0.59200;-2.93025;4.14479;,
 1.55289;-1.43986;4.87176;,
 1.71842;-4.12721;3.05917;,
 3.39865;-1.86934;3.42059;,
 1.55289;-1.43986;4.87176;,
 -1.26467;-4.74259;2.82311;,
 3.75287;-2.85570;0.68587;,
 2.40696;-5.44863;0.65369;,
 2.75375;-4.87340;-1.14692;,
 1.96881;-1.22051;-3.68196;,
 3.25954;-1.48186;-2.11904;,
 1.62572;-4.00898;-3.52358;,
 3.75287;-2.85570;0.68587;,
 2.75375;-4.87340;-1.14692;,
 3.75287;-2.85570;0.68587;,
 1.71842;-4.12721;3.05917;,
 2.40696;-5.44863;0.65369;,
 1.71842;-4.12721;3.05917;,
 3.39865;-1.86934;3.42059;,
 1.96881;-1.22051;-3.68196;,
 1.62572;-4.00898;-3.52358;,
 -0.66722;-2.22384;-4.83554;,
 -4.73831;-5.90397;-5.61601;,
 -3.42296;-3.46622;-4.86432;,
 -1.21204;-4.55533;-5.54248;,
 -2.14266;-6.56526;-6.53942;,
 -3.71863;-8.15413;-7.38780;,
 -4.73831;-5.90397;-5.61601;,
 -4.64954;-3.67561;-2.91636;,
 -3.42296;-3.46622;-4.86432;,
 -5.67198;-7.59263;-5.46735;,
 -4.73831;-5.90397;-5.61601;,
 -3.71863;-8.15413;-7.38780;,
 -5.27227;-7.31542;-3.01986;,
 -4.64954;-3.67561;-2.91636;,
 -4.73831;-5.90397;-5.61601;,
 -5.67198;-7.59263;-5.46735;,
 -5.27227;-7.31542;-3.01986;,
 -4.80955;-5.32028;-0.95897;,
 -4.64954;-3.67561;-2.91636;,
 -3.40407;-7.79855;-0.69840;,
 -3.49798;-5.71149;0.88769;,
 -4.80955;-5.32028;-0.95897;,
 -5.27227;-7.31542;-3.01986;,
 -5.27227;-7.31542;-3.01986;,
 -3.21893;-9.19089;-2.03603;,
 -3.40407;-7.79855;-0.69840;,
 -1.63884;-6.54016;1.37901;,
 -3.49798;-5.71149;0.88769;,
 -0.38797;-8.59494;-1.46854;,
 0.73790;-7.23691;-0.07216;,
 -1.63884;-6.54016;1.37901;,
 -3.40407;-7.79855;-0.69840;,
 -3.21893;-9.19089;-2.03603;,
 0.35088;-8.28232;-3.48322;,
 -0.38797;-8.59494;-1.46854;,
 -0.98248;-9.82276;-3.94884;,
 1.63392;-6.66302;-2.24921;,
 0.73790;-7.23691;-0.07216;,
 -0.22129;-7.56597;-5.30009;,
 0.35088;-8.28232;-3.48322;,
 -0.98248;-9.82276;-3.94884;,
 -1.51859;-9.19868;-6.46430;,
 0.96689;-5.71508;-4.18257;,
 1.63392;-6.66302;-2.24921;,
 -0.38797;-8.59494;-1.46854;,
 -3.21893;-9.19089;-2.03603;,
 -0.98248;-9.82276;-3.94884;,
 -2.14266;-6.56526;-6.53942;,
 -1.51859;-9.19868;-6.46430;,
 -3.71863;-8.15413;-7.38780;,
 -2.14266;-6.56526;-6.53942;,
 -0.22129;-7.56597;-5.30009;,
 -1.51859;-9.19868;-6.46430;,
 -1.21204;-4.55533;-5.54248;,
 0.96689;-5.71508;-4.18257;,
 -0.44883;-0.09131;-4.53969;,
 -2.78034;0.73868;-3.23653;,
 0.69113;1.50883;-0.75073;,
 -3.34818;1.18448;-0.56823;,
 0.69113;1.50883;-0.75073;,
 -2.78034;0.73868;-3.23653;,
 -3.34818;1.18448;-0.56823;,
 -2.61339;1.72957;1.48606;,
 0.69113;1.50883;-0.75073;,
 -2.61339;1.72957;1.48606;,
 -1.03279;1.86190;3.36745;,
 0.69113;1.50883;-0.75073;,
 -1.03279;1.86190;3.36745;,
 1.23039;1.54615;4.07332;,
 0.69113;1.50883;-0.75073;,
 3.28900;0.85094;3.33911;,
 0.69113;1.50883;-0.75073;,
 1.23039;1.54615;4.07332;,
 4.29986;-0.42358;-0.12144;,
 0.69113;1.50883;-0.75073;,
 4.45442;0.16296;1.89011;,
 0.69113;1.50883;-0.75073;,
 3.25954;-1.48186;-2.11904;,
 1.96881;-1.22051;-3.68196;,
 0.69113;1.50883;-0.75073;,
 4.29986;-0.42358;-0.12144;,
 4.45442;0.16296;1.89011;,
 0.69113;1.50883;-0.75073;,
 3.28900;0.85094;3.33911;,
 1.96881;-1.22051;-3.68196;,
 -0.44883;-0.09131;-4.53969;,
 0.69113;1.50883;-0.75073;,
 -4.41577;-1.53902;-0.95700;,
 -3.43796;-1.11175;-3.47757;,
 -4.64954;-3.67561;-2.91636;,
 -4.11762;-3.29708;1.02451;,
 -4.41577;-1.53902;-0.95700;,
 -4.64954;-3.67561;-2.91636;,
 -4.11762;-3.29708;1.02451;,
 -3.49798;-5.71149;0.88769;,
 -1.26467;-4.74259;2.82311;,
 -3.73459;-9.23418;-5.19616;,
 -3.73459;-9.23418;-5.19616;,
 -5.27227;-7.31542;-3.01986;,
 -5.67198;-7.59263;-5.46735;,
 -3.73459;-9.23418;-5.19616;,
 -3.73459;-9.23418;-5.19616;,
 -3.73459;-9.23418;-5.19616;,
 -3.73459;-9.23418;-5.19616;,
 -3.43796;-1.11175;-3.47757;,
 -2.78034;0.73868;-3.23653;,
 -0.44883;-0.09131;-4.53969;,
 -2.61339;1.72957;1.48606;,
 -3.21330;-1.49911;2.42827;,
 -1.03279;1.86190;3.36745;,
 -2.61339;1.72957;1.48606;,
 -3.21330;-1.49911;2.42827;,
 -1.53696;-0.67754;4.40071;,
 1.23039;1.54615;4.07332;,
 -1.03279;1.86190;3.36745;,
 -1.53696;-0.67754;4.40071;,
 -1.53696;-0.67754;4.40071;,
 1.55289;-1.43986;4.87176;,
 3.28900;0.85094;3.33911;,
 1.55289;-1.43986;4.87176;,
 3.39865;-1.86934;3.42059;,
 1.23039;1.54615;4.07332;,
 3.75287;-2.85570;0.68587;,
 4.29986;-0.42358;-0.12144;,
 4.45442;0.16296;1.89011;,
 3.25954;-1.48186;-2.11904;,
 4.29986;-0.42358;-0.12144;,
 3.75287;-2.85570;0.68587;,
 4.45442;0.16296;1.89011;,
 3.39865;-1.86934;3.42059;,
 3.75287;-2.85570;0.68587;,
 3.28900;0.85094;3.33911;,
 1.96881;-1.22051;-3.68196;,
 -0.66722;-2.22384;-4.83554;,
 -0.44883;-0.09131;-4.53969;,
 0.73955;-6.00014;1.50094;,
 1.71842;-4.12721;3.05917;,
 0.73955;-6.00014;1.50094;,
 -3.42296;-3.46622;-4.86432;,
 -0.66722;-2.22384;-4.83554;,
 -3.43796;-1.11175;-3.47757;,
 -3.42296;-3.46622;-4.86432;,
 -4.64954;-3.67561;-2.91636;,
 -3.43796;-1.11175;-3.47757;,
 -4.11762;-3.29708;1.02451;,
 -4.64954;-3.67561;-2.91636;,
 -4.11762;-3.29708;1.02451;,
 -1.63884;-6.54016;1.37901;,
 -1.26467;-4.74259;2.82311;,
 -3.49798;-5.71149;0.88769;,
 0.73955;-6.00014;1.50094;,
 -1.63884;-6.54016;1.37901;,
 0.73955;-6.00014;1.50094;,
 -1.26467;-4.74259;2.82311;,
 2.75375;-4.87340;-1.14692;,
 2.40696;-5.44863;0.65369;,
 1.62572;-4.00898;-3.52358;,
 2.75375;-4.87340;-1.14692;,
 2.40696;-5.44863;0.65369;,
 0.73955;-6.00014;1.50094;,
 0.73790;-7.23691;-0.07216;,
 1.62572;-4.00898;-3.52358;,
 -0.66722;-2.22384;-4.83554;;
 
 96;
 3;0,1,2;,
 3;3,4,5;,
 3;3,5,6;,
 3;7,8,9;,
 3;10,7,9;,
 3;11,12,13;,
 3;12,14,15;,
 3;12,15,13;,
 3;16,17,18;,
 3;19,20,21;,
 3;19,17,22;,
 3;17,19,21;,
 3;23,24,25;,
 3;26,27,28;,
 3;27,29,30;,
 3;27,30,28;,
 3;31,32,33;,
 3;34,31,35;,
 3;36,37,38;,
 3;39,40,41;,
 3;39,41,42;,
 3;43,39,42;,
 3;44,45,46;,
 3;47,48,49;,
 3;50,51,52;,
 3;53,50,52;,
 3;54,55,56;,
 3;57,58,59;,
 3;57,59,60;,
 3;57,61,62;,
 3;63,64,65;,
 3;66,67,68;,
 3;66,68,69;,
 3;70,66,69;,
 3;71,72,73;,
 3;72,71,74;,
 3;72,74,75;,
 3;76,77,78;,
 3;76,78,79;,
 3;77,76,80;,
 3;77,80,81;,
 3;82,83,84;,
 3;85,86,87;,
 3;88,89,90;,
 3;89,88,91;,
 3;89,91,92;,
 3;93,94,95;,
 3;96,97,98;,
 3;99,100,101;,
 3;102,103,104;,
 3;105,106,107;,
 3;108,109,110;,
 3;111,112,113;,
 3;114,115,116;,
 3;115,117,118;,
 3;119,120,121;,
 3;122,123,124;,
 3;125,126,127;,
 3;128,129,130;,
 3;131,132,133;,
 3;134,47,49;,
 3;135,136,137;,
 3;61,138,62;,
 3;139,79,78;,
 3;140,84,83;,
 3;141,87,86;,
 3;142,143,144;,
 3;145,8,146;,
 3;147,148,149;,
 3;147,149,150;,
 3;151,152,153;,
 3;151,154,155;,
 3;156,157,158;,
 3;157,156,159;,
 3;160,161,162;,
 3;163,164,165;,
 3;166,167,168;,
 3;167,166,169;,
 3;170,171,172;,
 3;173,174,22;,
 3;175,33,32;,
 3;176,177,41;,
 3;177,176,178;,
 3;179,180,181;,
 3;55,182,183;,
 3;58,184,59;,
 3;185,186,187;,
 3;67,188,189;,
 3;189,190,191;,
 3;192,193,75;,
 3;192,75,74;,
 3;194,195,81;,
 3;194,81,80;,
 3;196,197,198;,
 3;199,92,91;,
 3;200,199,91;;
 
 MeshMaterialList {
  7;
  96;
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
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.440920;0.449680;0.472310;1.000000;;
   23.000000;
   0.700000;0.700000;0.700000;;
   0.253680;0.258720;0.271740;;
  }
  Material {
   0.144000;0.144000;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.326400;0.332800;0.571200;1.000000;;
   31.000000;
   0.350000;0.350000;0.350000;;
   0.097920;0.099840;0.171360;;
  }
  Material {
   0.298000;0.245000;0.251000;1.000000;;
   46.000000;
   0.710000;0.710000;0.710000;;
   0.417200;0.343000;0.351400;;
  }
  Material {
   0.542400;0.545600;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.097600;0.097600;0.097600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;1.000000;0.898000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;1.000000;0.898000;;
  }
 }
 MeshNormals {
  62;
  -0.959996;0.279889;-0.008306;,
  -0.825562;0.071193;0.559802;,
  -0.428722;0.107211;0.897053;,
  -0.279678;-0.426996;0.859915;,
  0.418354;-0.610580;0.672438;,
  0.923094;-0.379126;0.064497;,
  0.854763;0.084593;-0.512079;,
  0.767421;-0.276432;0.578490;,
  0.116082;0.197105;-0.973486;,
  0.287765;0.252505;-0.923814;,
  -0.610934;0.484058;-0.626457;,
  -0.442258;0.429315;-0.787462;,
  -0.135186;0.352716;-0.925914;,
  -0.831499;0.428623;-0.353400;,
  -0.921853;-0.132219;0.364287;,
  -0.941098;-0.253596;0.223660;,
  -0.496089;-0.606957;0.620886;,
  -0.631008;-0.392559;0.669124;,
  -0.343303;-0.850995;0.397430;,
  -0.092173;-0.709315;0.698839;,
  0.548475;-0.756284;0.356666;,
  0.276143;0.303350;-0.911989;,
  0.857907;-0.487621;-0.161928;,
  0.822220;-0.531385;-0.203921;,
  0.785493;-0.127547;-0.605584;,
  0.752246;-0.165413;-0.637781;,
  0.671461;-0.099329;-0.734352;,
  0.366445;-0.823923;0.432284;,
  0.417974;-0.906256;-0.063225;,
  0.273141;0.923969;-0.267724;,
  -0.938716;0.325452;0.113546;,
  -0.146763;0.183468;-0.972008;,
  -0.654619;0.347608;-0.671299;,
  -0.880257;-0.052452;0.471589;,
  -0.309774;-0.488592;0.815670;,
  0.726935;-0.104526;-0.678704;,
  -0.444446;-0.888281;-0.115865;,
  -0.782728;0.357356;-0.509543;,
  -0.038112;0.987376;-0.153743;,
  0.079027;0.995501;-0.052267;,
  0.226675;0.973416;-0.032871;,
  0.354621;0.931970;-0.075339;,
  0.482188;0.756713;-0.441453;,
  0.448574;0.872283;-0.194688;,
  0.600619;0.289193;-0.745402;,
  0.722498;-0.617710;0.310534;,
  -0.955088;0.256660;-0.148095;,
  0.270912;-0.707828;0.652370;,
  0.882463;-0.426946;-0.197423;,
  0.247691;-0.119576;0.961432;,
  0.306676;0.840257;-0.447123;,
  0.003155;0.953947;-0.299958;,
  -0.087514;0.975038;-0.204066;,
  -0.636178;-0.766034;-0.092034;,
  -0.409100;-0.817313;-0.405754;,
  -0.172393;-0.929077;-0.327255;,
  -0.850646;0.286665;0.440708;,
  -0.607876;0.377543;0.698533;,
  0.034143;0.323013;0.945778;,
  0.621238;0.128259;0.773055;,
  0.950125;-0.267116;-0.160971;,
  0.941796;-0.167779;0.291324;;
  96;
  3;32,31,8;,
  3;0,30,37;,
  3;0,37,32;,
  3;1,30,0;,
  3;33,1,0;,
  3;2,1,3;,
  3;1,33,34;,
  3;1,34,3;,
  3;2,3,49;,
  3;4,7,49;,
  3;4,3,34;,
  3;3,4,49;,
  3;5,45,48;,
  3;44,6,35;,
  3;6,5,48;,
  3;6,48,35;,
  3;5,4,45;,
  3;4,5,7;,
  3;44,35,8;,
  3;10,11,9;,
  3;10,9,21;,
  3;12,10,21;,
  3;10,46,11;,
  3;13,10,12;,
  3;15,46,10;,
  3;13,15,10;,
  3;15,14,46;,
  3;16,17,14;,
  3;16,14,15;,
  3;16,15,18;,
  3;16,19,17;,
  3;27,20,19;,
  3;27,19,16;,
  3;18,27,16;,
  3;23,27,28;,
  3;27,23,22;,
  3;27,22,20;,
  3;25,23,28;,
  3;25,28,26;,
  3;23,25,24;,
  3;23,24,22;,
  3;27,18,28;,
  3;21,26,12;,
  3;21,25,26;,
  3;25,21,9;,
  3;25,9,24;,
  3;50,51,29;,
  3;52,29,51;,
  3;52,38,29;,
  3;38,39,29;,
  3;39,40,29;,
  3;41,29,40;,
  3;42,29,43;,
  3;29,6,44;,
  3;6,29,42;,
  3;43,29,41;,
  3;44,50,29;,
  3;0,32,46;,
  3;33,0,46;,
  3;33,17,34;,
  3;36,53,54;,
  3;36,15,53;,
  3;15,36,18;,
  3;36,55,28;,
  3;36,28,18;,
  3;36,54,55;,
  3;32,37,31;,
  3;56,30,1;,
  3;57,56,1;,
  3;57,1,2;,
  3;58,57,2;,
  3;58,2,49;,
  3;59,49,7;,
  3;49,59,58;,
  3;5,60,61;,
  3;6,60,5;,
  3;61,7,5;,
  3;7,61,59;,
  3;44,8,31;,
  3;47,4,34;,
  3;47,45,4;,
  3;11,8,9;,
  3;8,11,32;,
  3;11,46,32;,
  3;14,33,46;,
  3;17,33,14;,
  3;19,34,17;,
  3;20,47,19;,
  3;19,47,34;,
  3;48,45,20;,
  3;48,20,22;,
  3;35,48,22;,
  3;35,22,24;,
  3;45,47,20;,
  3;35,24,9;,
  3;8,35,9;;
 }
 MeshTextureCoords {
  201;
  0.138300;0.499900;,
  0.145100;0.498600;,
  0.144800;0.495800;,
  0.112900;0.503500;,
  0.113100;0.510900;,
  0.119900;0.509200;,
  0.119400;0.502900;,
  0.099100;0.504100;,
  0.104700;0.512900;,
  0.106000;0.504000;,
  0.099900;0.496400;,
  0.082900;0.512300;,
  0.084000;0.503800;,
  0.076200;0.503500;,
  0.085200;0.495300;,
  0.077300;0.494600;,
  0.067800;0.512700;,
  0.060900;0.503000;,
  0.060800;0.512800;,
  0.053400;0.502800;,
  0.046700;0.512100;,
  0.053700;0.512500;,
  0.061000;0.493400;,
  0.025400;0.501400;,
  0.032300;0.493700;,
  0.025300;0.492900;,
  0.174500;0.495600;,
  0.184500;0.494600;,
  0.183800;0.489300;,
  0.195200;0.493400;,
  0.193600;0.485100;,
  0.039500;0.502600;,
  0.045600;0.493300;,
  0.038900;0.493700;,
  0.046200;0.502700;,
  0.040000;0.511700;,
  0.165700;0.496400;,
  0.165700;0.493000;,
  0.158100;0.494200;,
  0.134100;0.453100;,
  0.136000;0.470100;,
  0.142300;0.469500;,
  0.139600;0.451800;,
  0.132300;0.437500;,
  0.123700;0.455700;,
  0.124100;0.471100;,
  0.129800;0.470700;,
  0.123400;0.441600;,
  0.128700;0.454500;,
  0.127700;0.439600;,
  0.113600;0.457900;,
  0.118500;0.471400;,
  0.118800;0.456800;,
  0.114500;0.445300;,
  0.102100;0.459600;,
  0.100400;0.472100;,
  0.106800;0.472000;,
  0.088500;0.460600;,
  0.086300;0.472400;,
  0.093600;0.472300;,
  0.095600;0.460100;,
  0.090700;0.449900;,
  0.083400;0.449900;,
  0.073500;0.459900;,
  0.070800;0.471900;,
  0.078600;0.472300;,
  0.059100;0.456900;,
  0.055600;0.470300;,
  0.063100;0.471300;,
  0.066100;0.458600;,
  0.062500;0.444600;,
  0.037700;0.448500;,
  0.042600;0.451300;,
  0.047300;0.437200;,
  0.032200;0.464100;,
  0.037700;0.466600;,
  0.169800;0.447300;,
  0.177500;0.446600;,
  0.169200;0.427200;,
  0.164200;0.431600;,
  0.175600;0.464200;,
  0.185900;0.465900;,
  0.047500;0.453400;,
  0.056700;0.442100;,
  0.051800;0.439800;,
  0.150300;0.449600;,
  0.152000;0.431700;,
  0.146800;0.432400;,
  0.156100;0.448800;,
  0.162500;0.448100;,
  0.157700;0.431400;,
  0.160400;0.467100;,
  0.167600;0.465900;,
  0.146600;0.516700;,
  0.140200;0.518400;,
  0.140900;0.521300;,
  0.115900;0.528400;,
  0.122700;0.527900;,
  0.122200;0.525500;,
  0.109200;0.531400;,
  0.102100;0.534400;,
  0.102600;0.536500;,
  0.094500;0.537200;,
  0.086100;0.539800;,
  0.086500;0.542000;,
  0.077300;0.541700;,
  0.068400;0.542500;,
  0.068500;0.544800;,
  0.051400;0.541400;,
  0.059500;0.544600;,
  0.059600;0.542400;,
  0.026100;0.532600;,
  0.025500;0.534600;,
  0.032200;0.536400;,
  0.183000;0.516200;,
  0.184000;0.514400;,
  0.174200;0.512700;,
  0.192800;0.518000;,
  0.194800;0.516300;,
  0.038100;0.538300;,
  0.043600;0.541900;,
  0.044100;0.540000;,
  0.165800;0.514500;,
  0.158800;0.514700;,
  0.159500;0.517200;,
  0.112900;0.490200;,
  0.118800;0.493400;,
  0.118900;0.490700;,
  0.100000;0.486800;,
  0.106700;0.489700;,
  0.106600;0.487200;,
  0.085500;0.488000;,
  0.085300;0.485900;,
  0.077400;0.485400;,
  0.123400;0.436500;,
  0.104500;0.444000;,
  0.103800;0.448200;,
  0.109400;0.446900;,
  0.084400;0.446000;,
  0.169000;0.426500;,
  0.058100;0.437300;,
  0.150500;0.425400;,
  0.138600;0.504000;,
  0.138900;0.508600;,
  0.145400;0.507000;,
  0.099500;0.522400;,
  0.097800;0.516800;,
  0.084000;0.526300;,
  0.092100;0.524600;,
  0.090800;0.518300;,
  0.082900;0.519100;,
  0.068000;0.528000;,
  0.075800;0.527400;,
  0.075000;0.519700;,
  0.067700;0.520200;,
  0.060700;0.520300;,
  0.053100;0.527500;,
  0.053600;0.520100;,
  0.046700;0.519500;,
  0.060500;0.528100;,
  0.026200;0.515500;,
  0.025800;0.521700;,
  0.033200;0.523900;,
  0.185000;0.506800;,
  0.196100;0.507900;,
  0.196800;0.501600;,
  0.039800;0.525400;,
  0.040000;0.518700;,
  0.033300;0.517400;,
  0.046100;0.526500;,
  0.165600;0.505400;,
  0.157900;0.500900;,
  0.157900;0.505500;,
  0.052900;0.489300;,
  0.053100;0.493200;,
  0.045300;0.489500;,
  0.137100;0.479900;,
  0.143600;0.479500;,
  0.137600;0.484800;,
  0.130500;0.480200;,
  0.124900;0.484900;,
  0.131000;0.485000;,
  0.099900;0.479700;,
  0.106500;0.479900;,
  0.092900;0.479600;,
  0.069700;0.478900;,
  0.077500;0.482800;,
  0.077700;0.479200;,
  0.054200;0.477900;,
  0.061900;0.478500;,
  0.053900;0.481500;,
  0.061600;0.482000;,
  0.029400;0.473200;,
  0.035300;0.475200;,
  0.178300;0.473500;,
  0.187100;0.471000;,
  0.041100;0.476400;,
  0.047100;0.477100;,
  0.048800;0.469200;,
  0.162400;0.477200;,
  0.155700;0.478300;;
 }
}