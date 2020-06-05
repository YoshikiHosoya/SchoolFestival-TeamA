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
 329;
 0.00000;18.53488;0.00000;,
 -4.54564;17.81069;-2.98982;,
 -6.42850;17.81069;0.00000;,
 0.00000;18.53488;0.00000;,
 0.00000;17.81069;-4.22825;,
 0.00000;18.53488;0.00000;,
 -4.54564;17.81069;2.98982;,
 0.00000;17.81069;4.22825;,
 0.00000;18.53488;0.00000;,
 -6.42850;17.81069;0.00000;,
 -8.39925;15.74843;-5.52448;,
 -11.87832;15.74843;-0.00001;,
 0.00000;15.74843;-7.81279;,
 -8.39924;15.74843;5.52448;,
 0.00000;15.74843;7.81279;,
 -11.87832;15.74843;-0.00001;,
 -10.97413;12.66205;-7.21808;,
 -15.51977;12.66205;-0.00001;,
 0.00000;12.66205;-10.20789;,
 -10.97413;12.66205;7.21807;,
 0.00000;12.66205;10.20789;,
 -15.51977;12.66205;-0.00001;,
 -11.87832;9.02139;-7.81281;,
 -16.79849;9.02139;-0.00001;,
 0.00000;9.02139;-11.04895;,
 -11.87832;9.02139;7.81278;,
 0.00000;9.02139;11.04895;,
 -16.79849;9.02139;-0.00001;,
 -10.97413;5.38074;-7.21808;,
 -15.51977;5.38074;-0.00001;,
 0.00000;5.38074;-10.20789;,
 -10.97413;5.38074;7.21807;,
 0.00000;5.38074;10.20789;,
 -15.51977;5.38074;-0.00001;,
 -8.39925;2.29434;-5.52448;,
 -11.87832;2.29434;-0.00001;,
 0.00000;2.29434;-7.81279;,
 -8.39924;2.29434;5.52448;,
 0.00000;2.29434;7.81279;,
 -11.87832;2.29434;-0.00001;,
 -4.54564;0.23208;-2.98982;,
 -6.42850;0.23208;0.00000;,
 0.00000;0.23208;-4.22825;,
 -4.54564;0.23208;2.98982;,
 0.00000;0.23208;4.22825;,
 -6.42850;0.23208;0.00000;,
 6.42850;17.81069;0.00000;,
 4.54564;17.81069;-2.98982;,
 4.54564;17.81069;2.98982;,
 6.42850;17.81069;0.00000;,
 11.87832;15.74843;-0.00001;,
 8.39925;15.74843;-5.52448;,
 8.39924;15.74843;5.52448;,
 11.87832;15.74843;-0.00001;,
 15.51977;12.66205;-0.00001;,
 10.97413;12.66205;-7.21808;,
 10.97413;12.66205;7.21807;,
 15.51977;12.66205;-0.00001;,
 16.79849;9.02139;-0.00001;,
 11.87832;9.02139;-7.81281;,
 11.87832;9.02139;7.81278;,
 16.79849;9.02139;-0.00001;,
 15.51977;5.38074;-0.00001;,
 10.97413;5.38074;-7.21808;,
 10.97413;5.38074;7.21807;,
 15.51977;5.38074;-0.00001;,
 11.87832;2.29434;-0.00001;,
 8.39925;2.29434;-5.52448;,
 8.39924;2.29434;5.52448;,
 11.87832;2.29434;-0.00001;,
 6.42850;0.23208;0.00000;,
 4.54564;0.23208;-2.98982;,
 4.54564;0.23208;2.98982;,
 6.42850;0.23208;0.00000;,
 -8.09994;23.35892;0.00000;,
 -9.73508;22.89895;-1.13613;,
 -10.41237;22.89895;0.00000;,
 -8.09994;23.35892;0.00000;,
 -8.09994;22.89895;-1.60674;,
 -8.09994;23.35892;0.00000;,
 -6.46482;22.89895;-1.13613;,
 -8.09994;23.35892;0.00000;,
 -5.78752;22.89895;0.00000;,
 -8.09994;23.35892;0.00000;,
 -6.46482;22.89895;1.13613;,
 -8.09994;23.35892;0.00000;,
 -8.09994;22.89895;1.60674;,
 -8.09994;23.35892;0.00000;,
 -9.73508;22.89895;1.13613;,
 -8.09994;23.35892;0.00000;,
 -10.41237;22.89895;0.00000;,
 -11.12127;21.58908;-2.09930;,
 -12.37274;21.58908;-0.00001;,
 -8.09994;21.58908;-2.96887;,
 -5.07863;21.58908;-2.09930;,
 -3.82715;21.58908;0.00000;,
 -5.07863;21.58908;2.09930;,
 -8.09994;21.58908;2.96887;,
 -11.12127;21.58908;2.09930;,
 -12.37274;21.58908;-0.00001;,
 -12.04749;19.62869;-2.74287;,
 -13.68263;19.62869;-0.00001;,
 -8.09994;19.62869;-3.87900;,
 -4.15241;19.62869;-2.74287;,
 -2.51727;19.62869;0.00000;,
 -4.15241;19.62869;2.74287;,
 -8.09994;19.62869;3.87900;,
 -12.04749;19.62869;2.74287;,
 -13.68263;19.62869;-0.00001;,
 -12.37274;17.31628;-2.96888;,
 -14.14259;17.31628;-0.00001;,
 -8.09994;17.31628;-4.19860;,
 -3.82715;17.31628;-2.96887;,
 -2.05730;17.31628;0.00000;,
 -3.82716;17.31628;2.96887;,
 -8.09994;17.31628;4.19860;,
 -12.37274;17.31628;2.96885;,
 -14.14259;17.31628;-0.00001;,
 -12.04749;15.00384;-2.74287;,
 -13.68263;15.00384;-0.00001;,
 -8.09994;15.00384;-3.87900;,
 -4.15241;15.00384;-2.74287;,
 -2.51727;15.00384;0.00000;,
 -4.15241;15.00384;2.74287;,
 -8.09994;15.00384;3.87900;,
 -12.04749;15.00384;2.74287;,
 -13.68263;15.00384;-0.00001;,
 -11.12127;13.04347;-2.09930;,
 -12.37274;13.04347;-0.00001;,
 -8.09994;13.04347;-2.96887;,
 -5.07863;13.04347;-2.09930;,
 -3.82715;13.04347;0.00000;,
 -5.07863;13.04347;2.09930;,
 -8.09994;13.04347;2.96887;,
 -11.12127;13.04347;2.09930;,
 -12.37274;13.04347;-0.00001;,
 10.41237;22.89895;0.00000;,
 9.73508;22.89895;-1.13613;,
 8.09994;23.35892;0.00000;,
 8.09994;22.89895;-1.60674;,
 8.09994;23.35892;0.00000;,
 6.46482;22.89895;-1.13613;,
 8.09994;23.35892;0.00000;,
 5.78752;22.89895;0.00000;,
 8.09994;23.35892;0.00000;,
 6.46482;22.89895;1.13613;,
 8.09994;23.35892;0.00000;,
 8.09994;22.89895;1.60674;,
 8.09994;23.35892;0.00000;,
 9.73508;22.89895;1.13613;,
 8.09994;23.35892;0.00000;,
 10.41237;22.89895;0.00000;,
 8.09994;23.35892;0.00000;,
 12.37274;21.58908;-0.00001;,
 11.12127;21.58908;-2.09930;,
 8.09994;21.58908;-2.96887;,
 5.07863;21.58908;-2.09930;,
 3.82715;21.58908;0.00000;,
 5.07863;21.58908;2.09930;,
 8.09994;21.58908;2.96887;,
 11.12127;21.58908;2.09930;,
 12.37274;21.58908;-0.00001;,
 13.68263;19.62869;-0.00001;,
 12.04749;19.62869;-2.74287;,
 8.09994;19.62869;-3.87900;,
 4.15241;19.62869;-2.74287;,
 2.51727;19.62869;0.00000;,
 4.15241;19.62869;2.74287;,
 8.09994;19.62869;3.87900;,
 12.04749;19.62869;2.74287;,
 13.68263;19.62869;-0.00001;,
 14.14259;17.31628;-0.00001;,
 12.37274;17.31628;-2.96888;,
 8.09994;17.31628;-4.19860;,
 3.82715;17.31628;-2.96887;,
 2.05730;17.31628;0.00000;,
 3.82716;17.31628;2.96887;,
 8.09994;17.31628;4.19860;,
 12.37274;17.31628;2.96885;,
 14.14259;17.31628;-0.00001;,
 13.68263;15.00384;-0.00001;,
 12.04749;15.00384;-2.74287;,
 8.09994;15.00384;-3.87900;,
 4.15241;15.00384;-2.74287;,
 2.51727;15.00384;0.00000;,
 4.15241;15.00384;2.74287;,
 8.09994;15.00384;3.87900;,
 12.04749;15.00384;2.74287;,
 13.68263;15.00384;-0.00001;,
 12.37274;13.04347;-0.00001;,
 11.12127;13.04347;-2.09930;,
 8.09994;13.04347;-2.96887;,
 5.07863;13.04347;-2.09930;,
 3.82715;13.04347;0.00000;,
 5.07863;13.04347;2.09930;,
 8.09994;13.04347;2.96887;,
 11.12127;13.04347;2.09930;,
 12.37274;13.04347;-0.00001;,
 -8.14627;20.91508;-2.89939;,
 -8.76218;20.79919;-3.22479;,
 -9.01729;20.74473;-2.93097;,
 -8.14627;20.91508;-2.89939;,
 -8.14627;20.82175;-3.34651;,
 -8.14627;20.91508;-2.89939;,
 -7.53037;20.79919;-3.22479;,
 -8.14627;20.91508;-2.89939;,
 -7.27526;20.74473;-2.93097;,
 -9.28431;20.36023;-3.56381;,
 -9.75571;20.25959;-3.02087;,
 -8.14627;20.40190;-3.78870;,
 -7.00823;20.36023;-3.56381;,
 -6.53684;20.25959;-3.02087;,
 -9.63320;19.66502;-3.86481;,
 -10.24911;19.53354;-3.15545;,
 -8.14627;19.71948;-4.15865;,
 -6.65935;19.66502;-3.86481;,
 -6.04345;19.53354;-3.15545;,
 -9.75571;18.81942;-4.08199;,
 -10.42236;18.67711;-3.31418;,
 -8.14627;18.87836;-4.40004;,
 -6.53684;18.81942;-4.08199;,
 -5.87019;18.67711;-3.31418;,
 -9.63320;17.95214;-4.18228;,
 -10.24911;17.82067;-3.47291;,
 -8.14627;18.00661;-4.47611;,
 -6.65935;17.95214;-4.18228;,
 -6.04345;17.82067;-3.47291;,
 -9.28431;17.19525;-4.15041;,
 -9.75571;17.09462;-3.60747;,
 -8.14627;17.23693;-4.37529;,
 -7.00823;17.19525;-4.15041;,
 -6.53684;17.09462;-3.60747;,
 -8.76218;16.66395;-3.99121;,
 -9.01729;16.60948;-3.69739;,
 -8.14627;16.68652;-4.11293;,
 -7.53037;16.66395;-3.99121;,
 -7.27526;16.60948;-3.69739;,
 -8.14627;16.43913;-3.72896;,
 -8.14627;16.43913;-3.72896;,
 -8.14627;16.43913;-3.72896;,
 -8.14627;16.43913;-3.72896;,
 9.01729;20.74473;-2.93097;,
 8.76218;20.79919;-3.22479;,
 8.14627;20.91508;-2.89939;,
 8.14627;20.82175;-3.34651;,
 8.14627;20.91508;-2.89939;,
 7.53037;20.79919;-3.22479;,
 8.14627;20.91508;-2.89939;,
 7.27526;20.74473;-2.93097;,
 8.14627;20.91508;-2.89939;,
 9.75571;20.25959;-3.02087;,
 9.28431;20.36023;-3.56381;,
 8.14627;20.40190;-3.78870;,
 7.00823;20.36023;-3.56381;,
 6.53684;20.25959;-3.02087;,
 10.24911;19.53354;-3.15545;,
 9.63320;19.66502;-3.86481;,
 8.14627;19.71948;-4.15865;,
 6.65935;19.66502;-3.86481;,
 6.04345;19.53354;-3.15545;,
 10.42236;18.67711;-3.31418;,
 9.75571;18.81942;-4.08199;,
 8.14627;18.87836;-4.40004;,
 6.53684;18.81942;-4.08199;,
 5.87019;18.67711;-3.31418;,
 10.24911;17.82067;-3.47291;,
 9.63320;17.95214;-4.18228;,
 8.14627;18.00661;-4.47611;,
 6.65935;17.95214;-4.18228;,
 6.04345;17.82067;-3.47291;,
 9.75571;17.09462;-3.60747;,
 9.28431;17.19525;-4.15041;,
 8.14627;17.23693;-4.37529;,
 7.00823;17.19525;-4.15041;,
 6.53684;17.09462;-3.60747;,
 9.01729;16.60948;-3.69739;,
 8.76218;16.66395;-3.99121;,
 8.14627;16.68652;-4.11293;,
 7.53037;16.66395;-3.99121;,
 7.27526;16.60948;-3.69739;,
 8.14627;16.43913;-3.72896;,
 8.14627;16.43913;-3.72896;,
 8.14627;16.43913;-3.72896;,
 8.14627;16.43913;-3.72896;,
 0.00000;7.25989;-10.69961;,
 0.00000;7.18296;-10.99706;,
 -3.33798;8.38098;-10.45408;,
 -3.24334;8.42381;-10.16140;,
 0.00000;6.91823;-11.15301;,
 -3.56649;8.19860;-10.59844;,
 0.00000;6.62077;-11.07607;,
 -3.79500;7.98346;-10.50994;,
 0.00000;6.46484;-10.81134;,
 -3.88965;7.86164;-10.24041;,
 0.00000;6.54176;-10.51389;,
 -3.79500;7.90445;-9.94775;,
 0.00000;6.80650;-10.35794;,
 -3.56649;8.08685;-9.80338;,
 0.00000;7.10395;-10.43487;,
 -3.33798;8.30198;-9.89189;,
 0.00000;7.25989;-10.69961;,
 -3.24334;8.42381;-10.16140;,
 -5.72147;10.71206;-9.23526;,
 -5.58761;10.67256;-8.95415;,
 -6.04462;10.72842;-9.35168;,
 -6.36779;10.71206;-9.23526;,
 -6.50163;10.67256;-8.95415;,
 -6.36779;10.63305;-8.67306;,
 -6.04462;10.61669;-8.55663;,
 -5.72147;10.63305;-8.67306;,
 -5.58761;10.67256;-8.95415;,
 3.24334;8.42381;-10.16140;,
 3.33798;8.38098;-10.45408;,
 3.56649;8.19860;-10.59844;,
 3.79500;7.98346;-10.50994;,
 3.88965;7.86164;-10.24041;,
 3.79500;7.90445;-9.94775;,
 3.56649;8.08685;-9.80338;,
 3.33798;8.30198;-9.89189;,
 3.24334;8.42381;-10.16140;,
 5.51694;10.67256;-8.95415;,
 5.65080;10.71206;-9.23526;,
 5.97395;10.72842;-9.35168;,
 6.29712;10.71206;-9.23526;,
 6.43096;10.67256;-8.95415;,
 6.29712;10.63305;-8.67306;,
 5.97395;10.61669;-8.55663;,
 5.65080;10.63305;-8.67306;,
 5.51694;10.67256;-8.95415;;
 
 248;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,7;,
 3;8,9,6;,
 4;2,1,10,11;,
 4;1,4,12,10;,
 4;7,6,13,14;,
 4;6,9,15,13;,
 4;11,10,16,17;,
 4;10,12,18,16;,
 4;14,13,19,20;,
 4;13,15,21,19;,
 4;17,16,22,23;,
 4;16,18,24,22;,
 4;20,19,25,26;,
 4;19,21,27,25;,
 4;23,22,28,29;,
 4;22,24,30,28;,
 4;26,25,31,32;,
 4;25,27,33,31;,
 4;29,28,34,35;,
 4;28,30,36,34;,
 4;32,31,37,38;,
 4;31,33,39,37;,
 4;35,34,40,41;,
 4;34,36,42,40;,
 4;38,37,43,44;,
 4;37,39,45,43;,
 3;46,47,0;,
 3;47,4,3;,
 3;7,48,5;,
 3;48,49,8;,
 4;50,51,47,46;,
 4;51,12,4,47;,
 4;14,52,48,7;,
 4;52,53,49,48;,
 4;54,55,51,50;,
 4;55,18,12,51;,
 4;20,56,52,14;,
 4;56,57,53,52;,
 4;58,59,55,54;,
 4;59,24,18,55;,
 4;26,60,56,20;,
 4;60,61,57,56;,
 4;62,63,59,58;,
 4;63,30,24,59;,
 4;32,64,60,26;,
 4;64,65,61,60;,
 4;66,67,63,62;,
 4;67,36,30,63;,
 4;38,68,64,32;,
 4;68,69,65,64;,
 4;70,71,67,66;,
 4;71,42,36,67;,
 4;44,72,68,38;,
 4;72,73,69,68;,
 3;74,75,76;,
 3;77,78,75;,
 3;79,80,78;,
 3;81,82,80;,
 3;83,84,82;,
 3;85,86,84;,
 3;87,88,86;,
 3;89,90,88;,
 4;76,75,91,92;,
 4;75,78,93,91;,
 4;78,80,94,93;,
 4;80,82,95,94;,
 4;82,84,96,95;,
 4;84,86,97,96;,
 4;86,88,98,97;,
 4;88,90,99,98;,
 4;92,91,100,101;,
 4;91,93,102,100;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;97,98,107,106;,
 4;98,99,108,107;,
 4;101,100,109,110;,
 4;100,102,111,109;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;104,105,114,113;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 4;107,108,117,116;,
 4;110,109,118,119;,
 4;109,111,120,118;,
 4;111,112,121,120;,
 4;112,113,122,121;,
 4;113,114,123,122;,
 4;114,115,124,123;,
 4;115,116,125,124;,
 4;116,117,126,125;,
 4;119,118,127,128;,
 4;118,120,129,127;,
 4;120,121,130,129;,
 4;121,122,131,130;,
 4;122,123,132,131;,
 4;123,124,133,132;,
 4;124,125,134,133;,
 4;125,126,135,134;,
 3;136,137,138;,
 3;137,139,140;,
 3;139,141,142;,
 3;141,143,144;,
 3;143,145,146;,
 3;145,147,148;,
 3;147,149,150;,
 3;149,151,152;,
 4;153,154,137,136;,
 4;154,155,139,137;,
 4;155,156,141,139;,
 4;156,157,143,141;,
 4;157,158,145,143;,
 4;158,159,147,145;,
 4;159,160,149,147;,
 4;160,161,151,149;,
 4;162,163,154,153;,
 4;163,164,155,154;,
 4;164,165,156,155;,
 4;165,166,157,156;,
 4;166,167,158,157;,
 4;167,168,159,158;,
 4;168,169,160,159;,
 4;169,170,161,160;,
 4;171,172,163,162;,
 4;172,173,164,163;,
 4;173,174,165,164;,
 4;174,175,166,165;,
 4;175,176,167,166;,
 4;176,177,168,167;,
 4;177,178,169,168;,
 4;178,179,170,169;,
 4;180,181,172,171;,
 4;181,182,173,172;,
 4;182,183,174,173;,
 4;183,184,175,174;,
 4;184,185,176,175;,
 4;185,186,177,176;,
 4;186,187,178,177;,
 4;187,188,179,178;,
 4;189,190,181,180;,
 4;190,191,182,181;,
 4;191,192,183,182;,
 4;192,193,184,183;,
 4;193,194,185,184;,
 4;194,195,186,185;,
 4;195,196,187,186;,
 4;196,197,188,187;,
 3;198,199,200;,
 3;201,202,199;,
 3;203,204,202;,
 3;205,206,204;,
 4;200,199,207,208;,
 4;199,202,209,207;,
 4;202,204,210,209;,
 4;204,206,211,210;,
 4;208,207,212,213;,
 4;207,209,214,212;,
 4;209,210,215,214;,
 4;210,211,216,215;,
 4;213,212,217,218;,
 4;212,214,219,217;,
 4;214,215,220,219;,
 4;215,216,221,220;,
 4;218,217,222,223;,
 4;217,219,224,222;,
 4;219,220,225,224;,
 4;220,221,226,225;,
 4;223,222,227,228;,
 4;222,224,229,227;,
 4;224,225,230,229;,
 4;225,226,231,230;,
 4;228,227,232,233;,
 4;227,229,234,232;,
 4;229,230,235,234;,
 4;230,231,236,235;,
 3;233,232,237;,
 3;232,234,238;,
 3;234,235,239;,
 3;235,236,240;,
 3;241,242,243;,
 3;242,244,245;,
 3;244,246,247;,
 3;246,248,249;,
 4;250,251,242,241;,
 4;251,252,244,242;,
 4;252,253,246,244;,
 4;253,254,248,246;,
 4;255,256,251,250;,
 4;256,257,252,251;,
 4;257,258,253,252;,
 4;258,259,254,253;,
 4;260,261,256,255;,
 4;261,262,257,256;,
 4;262,263,258,257;,
 4;263,264,259,258;,
 4;265,266,261,260;,
 4;266,267,262,261;,
 4;267,268,263,262;,
 4;268,269,264,263;,
 4;270,271,266,265;,
 4;271,272,267,266;,
 4;272,273,268,267;,
 4;273,274,269,268;,
 4;275,276,271,270;,
 4;276,277,272,271;,
 4;277,278,273,272;,
 4;278,279,274,273;,
 3;280,276,275;,
 3;281,277,276;,
 3;282,278,277;,
 3;283,279,278;,
 4;284,285,286,287;,
 4;285,288,289,286;,
 4;288,290,291,289;,
 4;290,292,293,291;,
 4;292,294,295,293;,
 4;294,296,297,295;,
 4;296,298,299,297;,
 4;298,300,301,299;,
 4;287,286,302,303;,
 4;286,289,304,302;,
 4;289,291,305,304;,
 4;291,293,306,305;,
 4;293,295,307,306;,
 4;295,297,308,307;,
 4;297,299,309,308;,
 4;299,301,310,309;,
 4;311,312,285,284;,
 4;312,313,288,285;,
 4;313,314,290,288;,
 4;314,315,292,290;,
 4;315,316,294,292;,
 4;316,317,296,294;,
 4;317,318,298,296;,
 4;318,319,300,298;,
 4;320,321,312,311;,
 4;321,322,313,312;,
 4;322,323,314,313;,
 4;323,324,315,314;,
 4;324,325,316,315;,
 4;325,326,317,316;,
 4;326,327,318,317;,
 4;327,328,319,318;;
 
 MeshMaterialList {
  1;
  248;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   1.000000;0.843137;0.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  281;
  -0.000000;1.000000;0.000000;,
  -0.233429;0.972374;0.000000;,
  -0.162733;0.956380;-0.242601;,
  0.000000;0.941031;-0.338320;,
  0.000000;0.941031;0.338320;,
  -0.162733;0.956380;0.242601;,
  -0.503720;0.863867;0.000000;,
  -0.337451;0.805511;-0.487114;,
  -0.000000;0.755006;-0.655717;,
  0.000000;0.755006;0.655718;,
  -0.337451;0.805510;0.487114;,
  -0.818016;0.575195;-0.000000;,
  -0.509643;0.491015;-0.706518;,
  0.000000;0.430229;-0.902720;,
  0.000000;0.430228;0.902720;,
  -0.509644;0.491014;0.706518;,
  -0.846184;-0.000000;-0.532891;,
  -0.592262;-0.000000;-0.805745;,
  0.000000;-0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.592263;-0.000000;0.805745;,
  -0.749716;-0.633704;-0.190643;,
  -0.509644;-0.491014;-0.706518;,
  0.000000;-0.430228;-0.902720;,
  0.000000;-0.430227;0.902721;,
  -0.509645;-0.491013;0.706518;,
  -0.503721;-0.863866;-0.000000;,
  -0.337452;-0.805510;-0.487115;,
  0.000000;-0.755005;-0.655719;,
  0.000000;-0.755005;0.655719;,
  -0.337452;-0.805509;0.487115;,
  -0.353917;-0.935277;0.000000;,
  -0.243838;-0.899930;-0.361483;,
  0.000000;-0.866786;-0.498680;,
  0.000000;-0.866786;0.498680;,
  -0.243838;-0.899930;0.361483;,
  0.233429;0.972374;0.000000;,
  0.162733;0.956380;-0.242601;,
  0.162733;0.956380;0.242601;,
  0.503720;0.863867;0.000000;,
  0.337451;0.805511;-0.487114;,
  0.337451;0.805510;0.487114;,
  0.818016;0.575195;-0.000000;,
  0.509643;0.491015;-0.706518;,
  0.509644;0.491014;0.706518;,
  0.846184;-0.000000;-0.532891;,
  0.592262;-0.000000;-0.805745;,
  0.592263;-0.000000;0.805745;,
  0.749716;-0.633704;-0.190643;,
  0.509644;-0.491014;-0.706518;,
  0.509645;-0.491013;0.706518;,
  0.503721;-0.863866;-0.000000;,
  0.337452;-0.805510;-0.487115;,
  0.337452;-0.805509;0.487115;,
  0.353917;-0.935277;0.000000;,
  0.243838;-0.899930;-0.361483;,
  0.243838;-0.899930;0.361483;,
  -0.846184;-0.000000;0.532891;,
  -0.811118;-0.284891;0.510808;,
  0.846184;-0.000000;0.532891;,
  0.811118;-0.284891;0.510808;,
  0.000000;1.000000;0.000000;,
  -0.378515;0.925595;-0.000000;,
  -0.260042;0.895403;-0.361431;,
  0.000001;0.867673;-0.497136;,
  0.260042;0.895402;-0.361432;,
  0.378514;0.925595;0.000000;,
  0.260042;0.895402;0.361432;,
  0.000001;0.867673;0.497136;,
  -0.260042;0.895402;0.361431;,
  -0.703031;0.711159;-0.000001;,
  -0.458370;0.639738;-0.616954;,
  0.000001;0.581900;-0.813261;,
  0.458371;0.639737;-0.616954;,
  0.703031;0.711159;0.000000;,
  0.458371;0.639737;0.616954;,
  0.000001;0.581900;0.813261;,
  -0.458371;0.639738;0.616953;,
  -0.922459;0.386096;-0.000001;,
  -0.573094;0.326070;-0.751826;,
  0.000001;0.282554;-0.959251;,
  0.573094;0.326069;-0.751825;,
  0.922458;0.386097;0.000000;,
  0.573094;0.326069;0.751826;,
  0.000000;0.282552;0.959252;,
  -0.573096;0.326068;0.751825;,
  -0.858952;0.000001;-0.512056;,
  -0.609643;0.000001;-0.792676;,
  0.000001;0.000001;-1.000000;,
  0.609644;0.000001;-0.792675;,
  0.858953;0.000001;-0.512055;,
  0.609643;0.000001;0.792676;,
  -0.000000;0.000001;1.000000;,
  -0.609644;0.000001;0.792675;,
  -0.878815;-0.437774;-0.189836;,
  -0.573093;-0.326071;-0.751826;,
  0.000001;-0.282555;-0.959251;,
  0.573094;-0.326071;-0.751825;,
  0.878816;-0.437773;-0.189835;,
  0.573094;-0.326070;0.751825;,
  0.000000;-0.282553;0.959252;,
  -0.573095;-0.326069;0.751825;,
  -0.831468;-0.555572;-0.000002;,
  -0.528594;-0.479667;-0.700363;,
  0.000001;-0.421098;-0.907015;,
  0.528595;-0.479667;-0.700363;,
  0.831469;-0.555570;-0.000000;,
  0.528595;-0.479667;0.700363;,
  0.000001;-0.421098;0.907015;,
  -0.528595;-0.479668;0.700361;,
  -0.000000;1.000000;0.000000;,
  0.378515;0.925595;-0.000000;,
  0.260042;0.895403;-0.361431;,
  -0.000001;0.867673;-0.497136;,
  -0.260042;0.895402;-0.361432;,
  -0.378514;0.925595;0.000000;,
  -0.260042;0.895402;0.361432;,
  -0.000001;0.867673;0.497136;,
  0.260042;0.895402;0.361431;,
  0.703031;0.711159;-0.000001;,
  0.458370;0.639738;-0.616954;,
  -0.000001;0.581900;-0.813261;,
  -0.458371;0.639737;-0.616954;,
  -0.703031;0.711159;0.000000;,
  -0.458371;0.639737;0.616954;,
  -0.000001;0.581900;0.813261;,
  0.458371;0.639738;0.616953;,
  0.922459;0.386096;-0.000001;,
  0.573094;0.326070;-0.751826;,
  -0.000001;0.282554;-0.959251;,
  -0.573094;0.326069;-0.751825;,
  -0.922458;0.386097;0.000000;,
  -0.573094;0.326069;0.751826;,
  -0.000000;0.282552;0.959252;,
  0.573096;0.326068;0.751825;,
  0.858952;0.000001;-0.512056;,
  0.609643;0.000001;-0.792676;,
  -0.000001;0.000001;-1.000000;,
  -0.609644;0.000001;-0.792675;,
  -0.858953;0.000001;-0.512055;,
  -0.609643;0.000001;0.792676;,
  0.000000;0.000001;1.000000;,
  0.609644;0.000001;0.792675;,
  0.878815;-0.437774;-0.189836;,
  0.573093;-0.326071;-0.751826;,
  -0.000001;-0.282555;-0.959251;,
  -0.573094;-0.326071;-0.751825;,
  -0.878816;-0.437773;-0.189835;,
  -0.573094;-0.326070;0.751825;,
  -0.000000;-0.282553;0.959252;,
  0.573095;-0.326069;0.751825;,
  0.831468;-0.555572;-0.000002;,
  0.528594;-0.479667;-0.700363;,
  -0.000001;-0.421098;-0.907015;,
  -0.528595;-0.479667;-0.700363;,
  -0.831469;-0.555570;0.000000;,
  -0.528595;-0.479667;0.700363;,
  -0.000001;-0.421098;0.907015;,
  0.528595;-0.479668;0.700361;,
  0.858952;0.000001;0.512056;,
  -0.858953;0.000001;0.512055;,
  0.846683;-0.168416;0.504742;,
  -0.846684;-0.168412;0.504741;,
  -0.858952;0.000001;0.512056;,
  0.858953;0.000001;0.512055;,
  -0.846683;-0.168416;0.504742;,
  0.846684;-0.168412;0.504741;,
  0.000001;0.995372;-0.096095;,
  -0.356809;0.923844;-0.138560;,
  -0.245540;0.920449;-0.304111;,
  0.000000;0.886447;-0.462830;,
  0.245541;0.920450;-0.304108;,
  0.356810;0.923844;-0.138559;,
  -0.600800;0.696371;-0.392566;,
  -0.405546;0.677088;-0.614071;,
  0.000000;0.608708;-0.793395;,
  0.405549;0.677089;-0.614068;,
  0.600804;0.696369;-0.392562;,
  -0.724257;0.412777;-0.552328;,
  -0.483177;0.413829;-0.771548;,
  0.000001;0.378533;-0.925588;,
  0.483180;0.413828;-0.771546;,
  0.724262;0.412775;-0.552324;,
  -0.760545;0.118325;-0.638413;,
  -0.505584;0.157230;-0.848330;,
  0.000001;0.182237;-0.983255;,
  0.505586;0.157230;-0.848329;,
  0.760547;0.118324;-0.638410;,
  -0.724257;-0.187422;-0.663569;,
  -0.483175;-0.109843;-0.868606;,
  0.000000;-0.021689;-0.999765;,
  0.483178;-0.109843;-0.868604;,
  0.724261;-0.187423;-0.663565;,
  -0.600791;-0.509433;-0.616058;,
  -0.405538;-0.412055;-0.815934;,
  0.000000;-0.283957;-0.958837;,
  0.405542;-0.412055;-0.815933;,
  0.600797;-0.509431;-0.616055;,
  -0.356800;-0.812813;-0.460465;,
  -0.245531;-0.750314;-0.613794;,
  0.000001;-0.661690;-0.749777;,
  0.245532;-0.750314;-0.613794;,
  0.356803;-0.812812;-0.460465;,
  0.000001;-0.894799;-0.446469;,
  -0.000001;0.995372;-0.096095;,
  0.356809;0.923844;-0.138560;,
  0.245540;0.920449;-0.304111;,
  -0.000000;0.886447;-0.462830;,
  -0.245541;0.920450;-0.304108;,
  -0.356810;0.923844;-0.138559;,
  0.600800;0.696371;-0.392566;,
  0.405546;0.677088;-0.614071;,
  -0.000000;0.608708;-0.793395;,
  -0.405549;0.677089;-0.614068;,
  -0.600804;0.696369;-0.392562;,
  0.724257;0.412777;-0.552328;,
  0.483177;0.413829;-0.771548;,
  -0.000001;0.378533;-0.925588;,
  -0.483180;0.413828;-0.771546;,
  -0.724262;0.412775;-0.552324;,
  0.760545;0.118325;-0.638413;,
  0.505584;0.157230;-0.848330;,
  -0.000001;0.182237;-0.983255;,
  -0.505586;0.157230;-0.848329;,
  -0.760547;0.118324;-0.638410;,
  0.724257;-0.187422;-0.663569;,
  0.483175;-0.109843;-0.868606;,
  -0.000000;-0.021689;-0.999765;,
  -0.483178;-0.109843;-0.868604;,
  -0.724261;-0.187423;-0.663565;,
  0.600791;-0.509433;-0.616058;,
  0.405538;-0.412055;-0.815934;,
  -0.000000;-0.283957;-0.958837;,
  -0.405542;-0.412055;-0.815933;,
  -0.600797;-0.509431;-0.616055;,
  0.356800;-0.812813;-0.460465;,
  0.245531;-0.750314;-0.613794;,
  -0.000001;-0.661690;-0.749777;,
  -0.245532;-0.750314;-0.613794;,
  -0.356803;-0.812812;-0.460465;,
  -0.000001;-0.894799;-0.446469;,
  0.000000;0.990105;0.140330;,
  0.000000;0.804533;-0.593908;,
  0.000000;0.177777;-0.984071;,
  -0.000000;-0.576559;-0.817055;,
  0.000000;-0.990125;-0.140189;,
  0.000000;-0.803680;0.595061;,
  -0.000000;-0.178170;0.984000;,
  0.000000;0.574784;0.818305;,
  0.550162;0.825779;0.124144;,
  0.312146;0.760080;-0.569950;,
  -0.093096;0.273447;-0.957371;,
  -0.475187;-0.396223;-0.785624;,
  -0.567114;-0.814701;-0.121013;,
  -0.327425;-0.747378;0.578117;,
  0.091181;-0.271015;0.958247;,
  0.474337;0.399202;0.784628;,
  0.720321;0.684712;0.110937;,
  0.427679;0.718814;-0.548084;,
  -0.096375;0.366576;-0.925383;,
  -0.615296;-0.222860;-0.756138;,
  -0.749644;-0.653687;-0.103575;,
  -0.452349;-0.692766;0.561654;,
  0.092426;-0.361348;0.927839;,
  0.609472;0.232726;0.757881;,
  -0.556355;0.821719;0.123479;,
  -0.315039;0.757462;-0.571840;,
  0.093347;0.274360;-0.957086;,
  0.478553;-0.391362;-0.786017;,
  0.572626;-0.810930;-0.120382;,
  0.330074;-0.744831;0.579895;,
  -0.091473;-0.272083;0.957916;,
  -0.478150;0.393808;0.785041;,
  -0.730752;0.673851;0.109206;,
  -0.433175;0.713017;-0.551332;,
  0.096852;0.368233;-0.924675;,
  0.620583;-0.212349;-0.754841;,
  0.758627;-0.643503;-0.101930;,
  0.457327;-0.687057;0.564628;,
  -0.092984;-0.363316;0.927014;,
  -0.615543;0.221061;0.756465;;
  248;
  3;0,2,1;,
  3;0,3,2;,
  3;0,5,4;,
  3;0,1,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;4,5,10,9;,
  4;5,1,6,10;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;9,10,15,14;,
  4;10,6,11,15;,
  4;11,12,17,16;,
  4;12,13,18,17;,
  4;14,15,20,19;,
  4;15,11,57,20;,
  4;16,17,22,21;,
  4;17,18,23,22;,
  4;19,20,25,24;,
  4;20,57,58,25;,
  4;21,22,27,26;,
  4;22,23,28,27;,
  4;24,25,30,29;,
  4;25,21,26,30;,
  4;26,27,32,31;,
  4;27,28,33,32;,
  4;29,30,35,34;,
  4;30,26,31,35;,
  3;36,37,0;,
  3;37,3,0;,
  3;4,38,0;,
  3;38,36,0;,
  4;39,40,37,36;,
  4;40,8,3,37;,
  4;9,41,38,4;,
  4;41,39,36,38;,
  4;42,43,40,39;,
  4;43,13,8,40;,
  4;14,44,41,9;,
  4;44,42,39,41;,
  4;45,46,43,42;,
  4;46,18,13,43;,
  4;19,47,44,14;,
  4;47,59,42,44;,
  4;48,49,46,45;,
  4;49,23,18,46;,
  4;24,50,47,19;,
  4;50,60,59,47;,
  4;51,52,49,48;,
  4;52,28,23,49;,
  4;29,53,50,24;,
  4;53,51,48,50;,
  4;54,55,52,51;,
  4;55,33,28,52;,
  4;34,56,53,29;,
  4;56,54,51,53;,
  3;61,63,62;,
  3;61,64,63;,
  3;61,65,64;,
  3;61,66,65;,
  3;61,67,66;,
  3;61,68,67;,
  3;61,69,68;,
  3;61,62,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,62,70,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,70,78,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,159;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,78,160,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;159,91,99,161;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,160,162,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,94,102,109;,
  3;111,112,110;,
  3;112,113,110;,
  3;113,114,110;,
  3;114,115,110;,
  3;115,116,110;,
  3;116,117,110;,
  3;117,118,110;,
  3;118,111,110;,
  4;119,120,112,111;,
  4;120,121,113,112;,
  4;121,122,114,113;,
  4;122,123,115,114;,
  4;123,124,116,115;,
  4;124,125,117,116;,
  4;125,126,118,117;,
  4;126,119,111,118;,
  4;127,128,120,119;,
  4;128,129,121,120;,
  4;129,130,122,121;,
  4;130,131,123,122;,
  4;131,132,124,123;,
  4;132,133,125,124;,
  4;133,134,126,125;,
  4;134,127,119,126;,
  4;135,136,128,127;,
  4;136,137,129,128;,
  4;137,138,130,129;,
  4;138,139,131,130;,
  4;163,140,132,131;,
  4;140,141,133,132;,
  4;141,142,134,133;,
  4;142,164,127,134;,
  4;143,144,136,135;,
  4;144,145,137,136;,
  4;145,146,138,137;,
  4;146,147,139,138;,
  4;165,148,140,163;,
  4;148,149,141,140;,
  4;149,150,142,141;,
  4;150,166,164,142;,
  4;151,152,144,143;,
  4;152,153,145,144;,
  4;153,154,146,145;,
  4;154,155,147,146;,
  4;155,156,148,147;,
  4;156,157,149,148;,
  4;157,158,150,149;,
  4;158,151,143,150;,
  3;167,169,168;,
  3;167,170,169;,
  3;167,171,170;,
  3;167,172,171;,
  4;168,169,174,173;,
  4;169,170,175,174;,
  4;170,171,176,175;,
  4;171,172,177,176;,
  4;173,174,179,178;,
  4;174,175,180,179;,
  4;175,176,181,180;,
  4;176,177,182,181;,
  4;178,179,184,183;,
  4;179,180,185,184;,
  4;180,181,186,185;,
  4;181,182,187,186;,
  4;183,184,189,188;,
  4;184,185,190,189;,
  4;185,186,191,190;,
  4;186,187,192,191;,
  4;188,189,194,193;,
  4;189,190,195,194;,
  4;190,191,196,195;,
  4;191,192,197,196;,
  4;193,194,199,198;,
  4;194,195,200,199;,
  4;195,196,201,200;,
  4;196,197,202,201;,
  3;198,199,203;,
  3;199,200,203;,
  3;200,201,203;,
  3;201,202,203;,
  3;205,206,204;,
  3;206,207,204;,
  3;207,208,204;,
  3;208,209,204;,
  4;210,211,206,205;,
  4;211,212,207,206;,
  4;212,213,208,207;,
  4;213,214,209,208;,
  4;215,216,211,210;,
  4;216,217,212,211;,
  4;217,218,213,212;,
  4;218,219,214,213;,
  4;220,221,216,215;,
  4;221,222,217,216;,
  4;222,223,218,217;,
  4;223,224,219,218;,
  4;225,226,221,220;,
  4;226,227,222,221;,
  4;227,228,223,222;,
  4;228,229,224,223;,
  4;230,231,226,225;,
  4;231,232,227,226;,
  4;232,233,228,227;,
  4;233,234,229,228;,
  4;235,236,231,230;,
  4;236,237,232,231;,
  4;237,238,233,232;,
  4;238,239,234,233;,
  3;240,236,235;,
  3;240,237,236;,
  3;240,238,237;,
  3;240,239,238;,
  4;241,242,250,249;,
  4;242,243,251,250;,
  4;243,244,252,251;,
  4;244,245,253,252;,
  4;245,246,254,253;,
  4;246,247,255,254;,
  4;247,248,256,255;,
  4;248,241,249,256;,
  4;249,250,258,257;,
  4;250,251,259,258;,
  4;251,252,260,259;,
  4;252,253,261,260;,
  4;253,254,262,261;,
  4;254,255,263,262;,
  4;255,256,264,263;,
  4;256,249,257,264;,
  4;265,266,242,241;,
  4;266,267,243,242;,
  4;267,268,244,243;,
  4;268,269,245,244;,
  4;269,270,246,245;,
  4;270,271,247,246;,
  4;271,272,248,247;,
  4;272,265,241,248;,
  4;273,274,266,265;,
  4;274,275,267,266;,
  4;275,276,268,267;,
  4;276,277,269,268;,
  4;277,278,270,269;,
  4;278,279,271,270;,
  4;279,280,272,271;,
  4;280,273,265,272;;
 }
 MeshTextureCoords {
  329;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.875000;0.375000;,
  0.750000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.875000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.875000;0.625000;,
  0.750000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.875000;0.875000;,
  0.750000;0.875000;,
  1.000000;0.875000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.875000;0.125000;,
  1.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.062500;0.000000;,
  0.250000;0.125000;,
  0.187500;0.000000;,
  0.375000;0.125000;,
  0.312500;0.000000;,
  0.500000;0.125000;,
  0.437500;0.000000;,
  0.625000;0.125000;,
  0.562500;0.000000;,
  0.750000;0.125000;,
  0.687500;0.000000;,
  0.875000;0.125000;,
  0.812500;0.000000;,
  1.000000;0.125000;,
  0.937500;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.062500;0.000000;,
  0.250000;0.125000;,
  0.187500;0.000000;,
  0.375000;0.125000;,
  0.312500;0.000000;,
  0.500000;0.125000;,
  0.437500;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.125000;0.375000;,
  0.125000;0.500000;,
  0.125000;0.625000;,
  0.125000;0.750000;,
  0.125000;0.875000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;;
 }
}