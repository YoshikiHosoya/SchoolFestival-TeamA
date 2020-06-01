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
 34;
 3.83377;-2.78091;-3.99415;,
 4.85738;-2.67314;-1.97643;,
 4.00592;-6.18534;-1.32373;,
 2.53249;-5.43381;-3.50047;,
 -2.62449;-5.29349;-3.93664;,
 0.50447;-3.01032;-6.64922;,
 0.68111;-6.39412;-3.32029;,
 -4.27161;-6.54867;-1.24752;,
 -4.42997;-3.08078;-1.89093;,
 -2.00045;-3.07179;-5.06269;,
 0.58817;-2.62537;5.64736;,
 -4.41408;-3.00775;0.44220;,
 -3.21892;-4.86603;3.17178;,
 0.73462;-7.20050;-1.13186;,
 -1.89966;-0.07121;-2.73549;,
 0.35211;1.17629;-2.68604;,
 0.41375;-0.53918;-4.40655;,
 -1.37799;-2.15224;-5.20338;,
 2.74710;-4.83075;2.82111;,
 0.67113;-4.73332;4.41387;,
 3.74170;-0.39893;-2.39729;,
 3.79445;-1.91973;-4.15395;,
 0.37704;1.05111;-0.31613;,
 3.73096;0.25703;-0.17232;,
 -2.70689;-1.35254;1.28646;,
 4.42783;-2.61966;0.36078;,
 3.73649;-0.08120;-1.31956;,
 4.69323;-2.64531;-0.84473;,
 4.01360;-6.14997;-0.19362;,
 0.75425;-7.42636;0.04672;,
 -3.49768;-6.43670;1.26073;,
 -4.42229;-3.04542;-0.76079;,
 -3.00771;-0.78053;-1.18261;,
 0.33384;1.78035;-1.66141;;
 
 40;
 4;0,1,2,3;,
 3;4,5,6;,
 4;7,8,9,4;,
 3;10,11,12;,
 4;6,13,7,4;,
 4;14,15,16,17;,
 3;5,3,6;,
 4;2,13,6,3;,
 3;18,10,19;,
 4;16,15,20,21;,
 3;22,10,23;,
 3;24,11,10;,
 4;17,9,8,14;,
 3;17,5,9;,
 3;21,5,16;,
 4;20,1,0,21;,
 3;5,0,3;,
 3;16,5,17;,
 3;21,0,5;,
 3;9,5,4;,
 3;25,10,18;,
 3;24,10,22;,
 3;10,12,19;,
 3;23,10,25;,
 4;26,27,1,20;,
 4;2,1,27,28;,
 4;28,29,13,2;,
 4;7,13,29,30;,
 4;30,31,8,7;,
 4;14,8,31,32;,
 4;32,33,15,14;,
 4;20,15,33,26;,
 4;23,25,27,26;,
 4;28,27,25,18;,
 4;18,19,29,28;,
 4;30,29,19,12;,
 4;11,31,30,12;,
 4;32,31,11,24;,
 4;24,22,33,32;,
 4;26,33,22,23;;
 
 MeshMaterialList {
  1;
  40;
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
   0.533333;0.687059;0.800000;0.890000;;
   11.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game314\\Documents\\Visual Studio 2015\\Projects\\C++3D2nd\\data\\Texture\\Ice.jpg";
   }
  }
 }
 MeshNormals {
  41;
  0.643325;0.680538;0.350715;,
  0.720904;-0.363922;0.589795;,
  0.611110;0.386741;-0.690635;,
  0.517495;-0.610888;-0.599178;,
  -0.481467;0.515036;-0.709174;,
  -0.444536;-0.555054;-0.703066;,
  -0.616842;0.669258;0.414246;,
  -0.899539;0.130599;0.416862;,
  0.017910;0.699758;-0.714156;,
  0.086083;-0.815276;-0.572639;,
  0.155405;-0.680996;0.715608;,
  -0.096058;0.915485;0.390717;,
  0.905892;0.123465;0.405112;,
  -0.414474;0.674604;0.610836;,
  -0.850506;0.330835;0.408885;,
  -0.680119;0.074548;-0.729302;,
  0.200491;-0.496874;-0.844346;,
  0.761380;-0.195205;-0.618220;,
  0.726366;0.576135;-0.374780;,
  0.976119;-0.003757;-0.217204;,
  0.687022;-0.680217;-0.255551;,
  0.082826;-0.967252;-0.239924;,
  -0.967659;-0.095956;-0.233300;,
  -0.924244;0.224804;-0.308603;,
  -0.634052;0.645964;-0.425098;,
  -0.019758;0.841142;-0.540454;,
  0.732822;0.678371;-0.052778;,
  0.988008;0.088639;0.126422;,
  0.838013;-0.430428;0.335360;,
  0.119466;-0.958382;0.259293;,
  -0.121418;-0.950886;0.284734;,
  -0.969752;0.232938;0.072950;,
  -0.697961;0.716114;0.005533;,
  -0.075933;0.995168;-0.062245;,
  -0.170615;-0.959101;-0.225866;,
  0.748287;-0.027211;0.662817;,
  -0.171000;0.553259;-0.815269;,
  -0.248624;-0.496458;0.831695;,
  -0.162303;-0.671070;0.723410;,
  0.324253;-0.942783;-0.077591;,
  -0.977697;-0.142897;0.153913;;
  40;
  4;17,19,20,3;,
  3;5,16,9;,
  4;22,23,15,5;,
  3;13,14,7;,
  4;9,21,34,5;,
  4;24,25,8,4;,
  3;16,3,9;,
  4;20,21,9,3;,
  3;1,35,10;,
  4;8,25,18,2;,
  3;11,13,0;,
  3;6,14,13;,
  4;4,15,23,24;,
  3;4,36,15;,
  3;2,36,8;,
  4;18,19,17,2;,
  3;16,17,3;,
  3;8,36,4;,
  3;2,17,16;,
  3;15,16,5;,
  3;12,35,1;,
  3;6,13,11;,
  3;37,38,10;,
  3;0,35,12;,
  4;26,27,19,18;,
  4;20,19,27,28;,
  4;39,29,21,20;,
  4;34,21,29,30;,
  4;40,31,23,22;,
  4;24,23,31,32;,
  4;32,33,25,24;,
  4;18,25,33,26;,
  4;0,12,27,26;,
  4;28,27,12,1;,
  4;1,10,29,28;,
  4;30,29,10,38;,
  4;14,31,40,7;,
  4;32,31,14,6;,
  4;6,11,33,32;,
  4;26,33,11,0;;
 }
 MeshTextureCoords {
  34;
  0.756556;0.235082;,
  0.766792;0.234005;,
  0.758277;0.269127;,
  0.743543;0.261611;,
  0.691973;0.260208;,
  0.723263;0.237376;,
  0.725029;0.271214;,
  0.675502;0.272760;,
  0.673918;0.238081;,
  0.698213;0.237991;,
  0.724100;0.233527;,
  0.674077;0.237351;,
  0.686029;0.255934;,
  0.725564;0.279278;,
  0.699221;0.207985;,
  0.721739;0.195510;,
  0.722355;0.212665;,
  0.704438;0.228796;,
  0.745689;0.255581;,
  0.724929;0.254606;,
  0.755635;0.211263;,
  0.756162;0.226470;,
  0.721988;0.196762;,
  0.755527;0.204703;,
  0.691149;0.220799;,
  0.762496;0.233470;,
  0.755583;0.208085;,
  0.765150;0.233726;,
  0.758354;0.268773;,
  0.725760;0.281537;,
  0.683241;0.271640;,
  0.673995;0.237727;,
  0.688141;0.215078;,
  0.721556;0.189470;;
 }
}
