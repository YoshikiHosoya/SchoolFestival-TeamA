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
 194;
 1.34093;118.47161;-18.71469;,
 13.99533;118.47161;-13.52507;,
 13.99533;-179.62906;-13.52507;,
 1.34093;-179.62906;-18.71469;,
 19.23698;118.47161;-0.99628;,
 19.23698;-179.62906;-0.99628;,
 13.99533;118.47161;11.53250;,
 13.99533;-179.62906;11.53250;,
 1.34093;118.47161;16.72211;,
 1.34093;-179.62906;16.72211;,
 -11.31347;118.47161;11.53250;,
 -11.31347;-179.62906;11.53250;,
 -16.55512;118.47161;-0.99628;,
 -16.55512;-179.62906;-0.99628;,
 -11.31347;118.47161;-13.52507;,
 -11.31347;-179.62906;-13.52507;,
 1.34093;118.47161;-18.71469;,
 1.34093;-179.62906;-18.71469;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;118.47161;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 1.34093;-179.62906;-0.99628;,
 -65.24880;44.15538;6.98631;,
 -0.81018;36.23412;6.98631;,
 -0.81018;36.23412;-9.37108;,
 -65.24880;44.15538;-9.37108;,
 -0.81018;36.23412;6.98631;,
 -3.28154;13.58397;6.98631;,
 -3.28154;13.58397;-9.37108;,
 -0.81018;36.23412;-9.37108;,
 -3.28154;13.58397;6.98631;,
 -70.08899;33.37718;6.98631;,
 -70.08899;33.37718;-9.37108;,
 -3.28154;13.58397;-9.37108;,
 -70.08899;33.37718;6.98631;,
 -65.24880;44.15538;6.98631;,
 -65.24880;44.15538;-9.37108;,
 -70.08899;33.37718;-9.37108;,
 -0.81018;36.23412;6.98631;,
 -65.24880;44.15538;6.98631;,
 -65.24880;44.15538;-9.37108;,
 -0.81018;36.23412;-9.37108;,
 73.62475;44.15538;-8.46076;,
 9.18621;36.23412;-8.46075;,
 9.18621;36.23412;7.89665;,
 73.62475;44.15538;7.89664;,
 9.18621;36.23412;-8.46075;,
 11.65756;13.58397;-8.46075;,
 11.65756;13.58397;7.89665;,
 9.18621;36.23412;7.89665;,
 11.65756;13.58397;-8.46075;,
 78.46496;33.37718;-8.46076;,
 78.46496;33.37718;7.89664;,
 11.65756;13.58397;7.89665;,
 78.46496;33.37718;-8.46076;,
 73.62475;44.15538;-8.46076;,
 73.62475;44.15538;7.89664;,
 78.46496;33.37718;7.89664;,
 9.18621;36.23412;-8.46075;,
 73.62475;44.15538;-8.46076;,
 73.62475;44.15538;7.89664;,
 9.18621;36.23412;7.89665;,
 -90.33701;103.51752;0.25739;,
 -112.76849;95.73870;-23.87263;,
 -133.11884;95.73870;5.19397;,
 -90.33701;103.51752;0.25739;,
 -69.76392;95.73870;-23.11597;,
 -90.33701;103.51752;0.25739;,
 -47.33223;95.73870;1.01406;,
 -90.33701;103.51752;0.25739;,
 -67.79401;95.73870;27.23407;,
 -90.33701;103.51752;0.25739;,
 -110.68737;95.73870;29.32402;,
 -90.33701;103.51752;0.25739;,
 -133.11884;95.73870;5.19397;,
 -126.63222;73.99739;-38.78590;,
 -159.62859;73.99739;6.48565;,
 -57.11783;73.99739;-39.32090;,
 -20.82233;73.99739;-0.27761;,
 -53.76421;75.42912;46.39733;,
 -123.33355;73.99739;45.52901;,
 -159.62859;73.99739;6.48565;,
 -126.52084;47.12383;-35.93925;,
 -159.62859;47.12383;6.48565;,
 -57.11783;47.12383;-39.32090;,
 -20.82233;47.12383;-0.27761;,
 -53.76421;48.55534;46.39733;,
 -123.33355;47.12383;45.52901;,
 -159.62859;47.12383;6.48565;,
 -112.65726;25.38255;-21.02601;,
 -133.11884;25.38255;5.19397;,
 -69.76392;25.38255;-23.11597;,
 -47.33223;25.38255;1.01406;,
 -67.79401;25.38255;27.23407;,
 -110.68737;25.38255;29.32402;,
 -133.11884;25.38255;5.19397;,
 -90.22563;17.07787;3.10403;,
 -90.22563;17.07787;3.10403;,
 -90.22563;17.07787;3.10403;,
 -90.22563;17.07787;3.10403;,
 -90.22563;17.07787;3.10403;,
 -90.22563;17.07787;3.10403;,
 102.91149;120.66606;-10.78803;,
 82.96892;109.80051;-35.06326;,
 65.16051;109.80051;-6.14189;,
 102.91149;120.66606;-10.78803;,
 120.94843;109.80051;-34.01617;,
 102.91149;120.66606;-10.78803;,
 140.89061;109.80051;-9.74092;,
 102.91149;120.66606;-10.78803;,
 122.96811;109.80051;16.33386;,
 102.91149;120.66606;-10.78803;,
 85.10271;109.80051;18.13338;,
 102.91149;120.66606;-10.78803;,
 65.16051;109.80051;-6.14189;,
 70.64388;79.43325;-50.06631;,
 41.75846;79.43325;-5.02972;,
 132.02531;79.43325;-50.13139;,
 164.29286;79.43325;-10.85310;,
 135.46352;81.43292;35.58692;,
 74.02599;79.43325;34.24857;,
 41.75846;79.43325;-5.02972;,
 70.75812;41.89665;-47.21968;,
 41.75846;41.89665;-5.02972;,
 132.02531;41.89665;-50.13139;,
 164.29286;41.89665;-10.85310;,
 135.46352;43.89610;35.58692;,
 74.02599;41.89665;34.24857;,
 41.75846;41.89665;-5.02972;,
 83.08311;11.52895;-32.21663;,
 65.16051;11.52895;-6.14189;,
 120.94843;11.52895;-34.01617;,
 140.89061;11.52895;-9.74092;,
 122.96811;11.52895;16.33386;,
 85.10271;11.52895;18.13338;,
 65.16051;11.52895;-6.14189;,
 103.02569;-0.07063;-7.94141;,
 103.02569;-0.07063;-7.94141;,
 103.02569;-0.07063;-7.94141;,
 103.02569;-0.07063;-7.94141;,
 103.02569;-0.07063;-7.94141;,
 103.02569;-0.07063;-7.94141;,
 0.78790;199.74680;-7.57908;,
 -25.08907;188.55127;-49.97618;,
 -47.87941;188.55127;0.16377;,
 0.78790;199.74680;-7.57908;,
 23.90861;188.55127;-47.81551;,
 0.78790;199.74680;-7.57908;,
 49.78537;188.55127;-5.41834;,
 0.78790;199.74680;-7.57908;,
 26.82982;188.55127;39.76991;,
 0.78790;199.74680;-7.57908;,
 -22.00273;188.55127;42.56099;,
 0.78790;199.74680;-7.57908;,
 -47.87941;188.55127;0.16377;,
 -41.08174;157.26160;-76.17929;,
 -78.05963;157.26160;1.88874;,
 38.09599;157.26160;-75.74355;,
 79.96582;157.26160;-7.14333;,
 43.06911;159.32178;73.36601;,
 -36.18999;157.26160;70.48910;,
 -78.05963;157.26160;1.88874;,
 -40.91658;118.58508;-71.22747;,
 -78.05963;118.58508;1.88874;,
 38.09599;118.58508;-75.74355;,
 79.96582;118.58508;-7.14333;,
 43.06911;120.64561;73.36601;,
 -36.18999;118.58508;70.48910;,
 -78.05963;118.58508;1.88874;,
 -24.92390;87.29480;-45.02441;,
 -47.87941;87.29480;0.16377;,
 23.90861;87.29480;-47.81551;,
 49.78537;87.29480;-5.41834;,
 26.82982;87.29480;39.76991;,
 -22.00273;87.29480;42.56099;,
 -47.87941;87.29480;0.16377;,
 0.95305;75.34270;-2.62729;,
 0.95305;75.34270;-2.62729;,
 0.95305;75.34270;-2.62729;,
 0.95305;75.34270;-2.62729;,
 0.95305;75.34270;-2.62729;,
 0.95305;75.34270;-2.62729;;
 
 126;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;46,39,50,51;,
 4;52,53,40,49;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;66,59,70,71;,
 4;72,73,60,69;,
 3;74,75,76;,
 3;77,78,75;,
 3;79,80,78;,
 3;81,82,80;,
 3;83,84,82;,
 3;85,86,84;,
 4;76,75,87,88;,
 4;75,78,89,87;,
 4;78,80,90,89;,
 4;80,82,91,90;,
 4;82,84,92,91;,
 4;84,86,93,92;,
 4;88,87,94,95;,
 4;87,89,96,94;,
 4;89,90,97,96;,
 4;90,91,98,97;,
 4;91,92,99,98;,
 4;92,93,100,99;,
 4;95,94,101,102;,
 4;94,96,103,101;,
 4;96,97,104,103;,
 4;97,98,105,104;,
 4;98,99,106,105;,
 4;99,100,107,106;,
 3;102,101,108;,
 3;101,103,109;,
 3;103,104,110;,
 3;104,105,111;,
 3;105,106,112;,
 3;106,107,113;,
 3;114,115,116;,
 3;117,118,115;,
 3;119,120,118;,
 3;121,122,120;,
 3;123,124,122;,
 3;125,126,124;,
 4;116,115,127,128;,
 4;115,118,129,127;,
 4;118,120,130,129;,
 4;120,122,131,130;,
 4;122,124,132,131;,
 4;124,126,133,132;,
 4;128,127,134,135;,
 4;127,129,136,134;,
 4;129,130,137,136;,
 4;130,131,138,137;,
 4;131,132,139,138;,
 4;132,133,140,139;,
 4;135,134,141,142;,
 4;134,136,143,141;,
 4;136,137,144,143;,
 4;137,138,145,144;,
 4;138,139,146,145;,
 4;139,140,147,146;,
 3;142,141,148;,
 3;141,143,149;,
 3;143,144,150;,
 3;144,145,151;,
 3;145,146,152;,
 3;146,147,153;,
 3;154,155,156;,
 3;157,158,155;,
 3;159,160,158;,
 3;161,162,160;,
 3;163,164,162;,
 3;165,166,164;,
 4;156,155,167,168;,
 4;155,158,169,167;,
 4;158,160,170,169;,
 4;160,162,171,170;,
 4;162,164,172,171;,
 4;164,166,173,172;,
 4;168,167,174,175;,
 4;167,169,176,174;,
 4;169,170,177,176;,
 4;170,171,178,177;,
 4;171,172,179,178;,
 4;172,173,180,179;,
 4;175,174,181,182;,
 4;174,176,183,181;,
 4;176,177,184,183;,
 4;177,178,185,184;,
 4;178,179,186,185;,
 4;179,180,187,186;,
 3;182,181,188;,
 3;181,183,189;,
 3;183,184,190;,
 3;184,185,191;,
 3;185,186,192;,
 3;186,187,193;;
 
 MeshMaterialList {
  3;
  126;
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.432800;0.300800;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.263529;0.059608;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  114;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.704608;0.000000;-0.709597;,
  1.000000;0.000000;0.000000;,
  0.704608;0.000000;0.709597;,
  0.000000;0.000000;1.000000;,
  -0.704608;0.000000;0.709597;,
  -1.000000;0.000000;0.000000;,
  -0.704608;0.000000;-0.709596;,
  0.000000;-1.000000;-0.000000;,
  0.122009;0.992529;0.000000;,
  0.994100;-0.108466;-0.000000;,
  -0.284067;-0.958804;0.000000;,
  -0.912238;0.409661;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.122009;0.992529;0.000000;,
  -0.994100;-0.108466;0.000000;,
  0.284068;-0.958804;-0.000000;,
  0.912237;0.409662;0.000000;,
  -0.000000;-0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.003162;0.999941;-0.010348;,
  -0.408487;0.912449;0.023979;,
  -0.210869;0.864747;-0.455792;,
  0.194114;0.855913;-0.479305;,
  0.396071;0.917589;-0.034027;,
  0.200995;0.886142;0.417557;,
  -0.180925;0.876139;0.446819;,
  -0.637398;0.769443;0.041002;,
  -0.418893;0.349459;-0.838097;,
  0.359747;0.351624;-0.864259;,
  0.613200;0.788158;-0.052839;,
  0.408137;0.410569;0.815388;,
  -0.367422;0.385295;0.846492;,
  -0.734632;-0.379796;-0.562201;,
  -0.415230;-0.387137;-0.823231;,
  0.344859;-0.378590;-0.858919;,
  0.681376;-0.366747;-0.633422;,
  0.412057;-0.388840;0.824022;,
  -0.363075;-0.376211;0.852433;,
  -0.411206;-0.911388;0.016780;,
  -0.223172;-0.856413;-0.465566;,
  0.177872;-0.857853;-0.482131;,
  0.408192;-0.912652;-0.021128;,
  0.214897;-0.866631;0.450300;,
  -0.182029;-0.863311;0.470701;,
  -0.000000;-1.000000;-0.000000;,
  -0.797908;-0.032822;-0.601885;,
  0.732410;0.000000;-0.680864;,
  0.817010;0.000000;0.576623;,
  0.749489;-0.374453;0.545941;,
  -0.732415;0.000000;0.680859;,
  -0.681381;-0.366747;0.633417;,
  0.005000;0.999900;-0.013254;,
  -0.546413;0.836927;0.031411;,
  -0.277170;0.793070;-0.542418;,
  0.262571;0.778915;-0.569516;,
  0.535164;0.843795;-0.040121;,
  0.269323;0.819942;0.505133;,
  -0.243683;0.807090;0.537796;,
  -0.809972;0.262360;-0.524512;,
  -0.458292;0.270634;-0.846597;,
  0.404397;0.270463;-0.873678;,
  0.936120;0.345596;-0.065135;,
  0.449754;0.324267;0.832210;,
  -0.412344;0.299530;0.860380;,
  -0.795195;-0.282425;-0.536564;,
  -0.458661;-0.297643;-0.837280;,
  0.389062;-0.291174;-0.873984;,
  0.743234;-0.273501;-0.610574;,
  0.452640;-0.303223;0.838554;,
  -0.407765;-0.290921;0.865502;,
  -0.463378;-0.870235;-0.167245;,
  -0.293351;-0.780927;-0.551451;,
  0.241101;-0.782490;-0.574091;,
  0.446799;-0.870882;-0.204784;,
  0.284680;-0.792590;0.539220;,
  -0.246003;-0.788060;0.564308;,
  0.000001;-1.000000;-0.000000;,
  -0.743234;0.273502;0.610573;,
  0.807270;-0.280903;0.519045;,
  -0.743235;-0.273499;0.610574;,
  0.699736;-0.539117;0.468746;,
  -0.657099;-0.526142;0.539811;,
  0.004236;0.999953;-0.008774;,
  -0.484532;0.874438;0.024215;,
  -0.247674;0.884190;-0.396062;,
  0.244885;0.874394;-0.418888;,
  0.477123;0.878352;-0.029181;,
  0.242612;0.899920;0.362331;,
  -0.227506;0.893513;0.387137;,
  -0.925096;0.376919;0.046148;,
  -0.497700;0.375323;-0.781938;,
  0.453041;0.376277;-0.808189;,
  0.918346;0.391958;-0.054854;,
  0.483107;0.435384;0.759637;,
  -0.463901;0.411834;0.784340;,
  -0.918827;-0.392772;0.038574;,
  -0.624236;-0.508852;-0.592789;,
  0.222305;-0.523120;-0.822755;,
  0.920936;-0.386662;-0.048670;,
  0.626858;-0.525056;0.575643;,
  -0.458034;-0.403389;0.792138;,
  -0.489341;-0.871915;0.017567;,
  -0.267426;-0.874736;-0.404129;,
  0.222818;-0.878599;-0.422394;,
  0.487509;-0.872882;-0.020302;,
  0.257649;-0.884033;0.390004;,
  -0.228800;-0.883005;0.409819;,
  0.000000;-1.000000;-0.000000;,
  -0.025867;-0.063645;-0.997637;,
  0.853573;0.000000;-0.520974;,
  -0.036274;0.000000;0.999342;;
  126;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  3;22,24,23;,
  3;22,25,24;,
  3;22,26,25;,
  3;22,27,26;,
  3;22,28,27;,
  3;22,23,28;,
  4;23,24,30,29;,
  4;24,25,31,30;,
  4;25,26,32,31;,
  4;26,27,33,32;,
  4;27,28,34,33;,
  4;28,23,29,34;,
  4;48,30,36,35;,
  4;30,31,37,36;,
  4;31,49,38,37;,
  4;50,33,39,51;,
  4;33,34,40,39;,
  4;34,52,53,40;,
  4;35,36,42,41;,
  4;36,37,43,42;,
  4;37,38,44,43;,
  4;51,39,45,44;,
  4;39,40,46,45;,
  4;40,53,41,46;,
  3;41,42,47;,
  3;42,43,47;,
  3;43,44,47;,
  3;44,45,47;,
  3;45,46,47;,
  3;46,41,47;,
  3;54,56,55;,
  3;54,57,56;,
  3;54,58,57;,
  3;54,59,58;,
  3;54,60,59;,
  3;54,55,60;,
  4;55,56,62,61;,
  4;56,57,63,62;,
  4;57,58,64,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,55,80,66;,
  4;61,62,68,67;,
  4;62,63,69,68;,
  4;63,64,70,69;,
  4;64,65,71,81;,
  4;65,66,72,71;,
  4;66,80,82,72;,
  4;67,68,74,73;,
  4;68,69,75,74;,
  4;69,70,76,75;,
  4;81,71,77,83;,
  4;71,72,78,77;,
  4;72,82,84,78;,
  3;73,74,79;,
  3;74,75,79;,
  3;75,76,79;,
  3;76,77,79;,
  3;77,78,79;,
  3;78,73,79;,
  3;85,87,86;,
  3;85,88,87;,
  3;85,89,88;,
  3;85,90,89;,
  3;85,91,90;,
  3;85,86,91;,
  4;86,87,93,92;,
  4;87,88,94,93;,
  4;88,89,95,94;,
  4;89,90,96,95;,
  4;90,91,97,96;,
  4;91,86,92,97;,
  4;92,93,99,98;,
  4;93,94,100,111;,
  4;94,95,101,112;,
  4;95,96,102,101;,
  4;96,97,103,113;,
  4;97,92,98,103;,
  4;98,99,105,104;,
  4;99,100,106,105;,
  4;100,101,107,106;,
  4;101,102,108,107;,
  4;102,103,109,108;,
  4;103,98,104,109;,
  3;104,105,110;,
  3;105,106,110;,
  3;106,107,110;,
  3;107,108,110;,
  3;108,109,110;,
  3;109,104,110;;
 }
 MeshTextureCoords {
  194;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.083333;0.000000;,
  0.166667;0.200000;,
  0.000000;0.200000;,
  0.250000;0.000000;,
  0.333333;0.200000;,
  0.416667;0.000000;,
  0.500000;0.200000;,
  0.583333;0.000000;,
  0.666667;0.200000;,
  0.750000;0.000000;,
  0.833333;0.200000;,
  0.916667;0.000000;,
  1.000000;0.200000;,
  0.166667;0.400000;,
  0.000000;0.400000;,
  0.333333;0.400000;,
  0.500000;0.400000;,
  0.666667;0.400000;,
  0.833333;0.400000;,
  1.000000;0.400000;,
  0.166667;0.600000;,
  0.000000;0.600000;,
  0.333333;0.600000;,
  0.500000;0.600000;,
  0.666667;0.600000;,
  0.833333;0.600000;,
  1.000000;0.600000;,
  0.166667;0.800000;,
  0.000000;0.800000;,
  0.333333;0.800000;,
  0.500000;0.800000;,
  0.666667;0.800000;,
  0.833333;0.800000;,
  1.000000;0.800000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;,
  0.083333;0.000000;,
  0.166667;0.200000;,
  0.000000;0.200000;,
  0.250000;0.000000;,
  0.333333;0.200000;,
  0.416667;0.000000;,
  0.500000;0.200000;,
  0.583333;0.000000;,
  0.666667;0.200000;,
  0.750000;0.000000;,
  0.833333;0.200000;,
  0.916667;0.000000;,
  1.000000;0.200000;,
  0.166667;0.400000;,
  0.000000;0.400000;,
  0.333333;0.400000;,
  0.500000;0.400000;,
  0.666667;0.400000;,
  0.833333;0.400000;,
  1.000000;0.400000;,
  0.166667;0.600000;,
  0.000000;0.600000;,
  0.333333;0.600000;,
  0.500000;0.600000;,
  0.666667;0.600000;,
  0.833333;0.600000;,
  1.000000;0.600000;,
  0.166667;0.800000;,
  0.000000;0.800000;,
  0.333333;0.800000;,
  0.500000;0.800000;,
  0.666667;0.800000;,
  0.833333;0.800000;,
  1.000000;0.800000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;,
  0.083333;0.000000;,
  0.166667;0.200000;,
  0.000000;0.200000;,
  0.250000;0.000000;,
  0.333333;0.200000;,
  0.416667;0.000000;,
  0.500000;0.200000;,
  0.583333;0.000000;,
  0.666667;0.200000;,
  0.750000;0.000000;,
  0.833333;0.200000;,
  0.916667;0.000000;,
  1.000000;0.200000;,
  0.166667;0.400000;,
  0.000000;0.400000;,
  0.333333;0.400000;,
  0.500000;0.400000;,
  0.666667;0.400000;,
  0.833333;0.400000;,
  1.000000;0.400000;,
  0.166667;0.600000;,
  0.000000;0.600000;,
  0.333333;0.600000;,
  0.500000;0.600000;,
  0.666667;0.600000;,
  0.833333;0.600000;,
  1.000000;0.600000;,
  0.166667;0.800000;,
  0.000000;0.800000;,
  0.333333;0.800000;,
  0.500000;0.800000;,
  0.666667;0.800000;,
  0.833333;0.800000;,
  1.000000;0.800000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;;
 }
}
