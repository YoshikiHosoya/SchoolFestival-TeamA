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
 302;
 16.37052;25.61285;7.80809;,
 19.87222;25.61285;7.80809;,
 19.87222;27.12290;3.78079;,
 16.37052;27.12290;3.78079;,
 19.87222;27.72717;-0.32059;,
 16.37052;27.72717;-0.32059;,
 16.37052;0.36727;7.80809;,
 16.37052;0.36727;3.78079;,
 19.87222;0.36727;3.78079;,
 19.87222;0.36727;7.80809;,
 16.37052;0.36727;-0.32059;,
 19.87222;0.36727;-0.32059;,
 19.87222;27.10101;-4.15737;,
 16.37052;27.10101;-4.15737;,
 19.87222;25.61285;-7.77188;,
 16.37052;25.61285;-7.77188;,
 16.37052;0.36727;-4.15737;,
 19.87222;0.36727;-4.15737;,
 16.37052;0.36727;-7.77188;,
 19.87222;0.36727;-7.77188;,
 16.37052;17.96811;-15.57674;,
 16.37052;23.70523;-11.83091;,
 19.87222;23.70523;-11.83091;,
 19.87222;17.96811;-15.57674;,
 16.37052;0.36727;-15.57674;,
 19.87222;0.36727;-15.57674;,
 19.87222;0.36727;-11.83092;,
 16.37052;0.36727;-11.83092;,
 16.37051;17.96811;14.93555;,
 19.87222;17.96811;14.93555;,
 19.87222;23.81462;11.32205;,
 16.37051;23.81462;11.32205;,
 16.37051;0.36727;14.93555;,
 16.37051;0.36727;11.32205;,
 19.87222;0.36727;11.32205;,
 19.87222;0.36727;14.93555;,
 -16.45272;27.12290;3.78079;,
 -19.87222;27.12290;3.78079;,
 -19.87222;25.61285;7.80809;,
 -16.45272;25.61285;7.80809;,
 -16.45272;27.72717;-0.32059;,
 -19.87222;27.72717;-0.32059;,
 -16.45272;0.36727;7.80809;,
 -19.87222;0.36727;7.80809;,
 -19.87222;0.36727;3.78079;,
 -16.45272;0.36727;3.78079;,
 -19.87222;0.36727;-0.32059;,
 -16.45272;0.36727;-0.32059;,
 -16.45272;27.10101;-4.15737;,
 -19.87222;27.10101;-4.15737;,
 -16.45272;25.61285;-7.77188;,
 -19.87222;25.61285;-7.77188;,
 -19.87222;0.36727;-4.15737;,
 -16.45272;0.36727;-4.15737;,
 -19.87222;0.36727;-7.77188;,
 -16.45272;0.36727;-7.77188;,
 -16.45272;17.96811;-15.57674;,
 -19.87222;17.96811;-15.57674;,
 -19.87222;23.70523;-11.83091;,
 -16.45272;23.70523;-11.83091;,
 -16.45272;0.36727;-11.83092;,
 -19.87222;0.36727;-11.83092;,
 -19.87222;0.36727;-15.57674;,
 -16.45272;0.36727;-15.57674;,
 -16.45272;23.81462;11.32205;,
 -19.87222;23.81462;11.32205;,
 -19.87222;17.96811;14.93555;,
 -16.45272;17.96811;14.93555;,
 -16.45272;0.36727;14.93555;,
 -19.87222;0.36727;14.93555;,
 -19.87222;0.36727;11.32205;,
 -16.45272;0.36727;11.32205;,
 19.87222;12.64564;7.80809;,
 19.87222;0.36727;7.80809;,
 19.87222;0.36727;3.78079;,
 19.87222;12.64564;3.78079;,
 19.87222;0.36727;-0.32059;,
 19.87222;12.64564;-0.32059;,
 -19.87222;12.64564;7.80809;,
 -19.87222;12.64564;3.78079;,
 -19.87222;0.36727;3.78079;,
 -19.87222;0.36727;7.80809;,
 -19.87222;12.64564;-0.32059;,
 -19.87222;0.36727;-0.32059;,
 19.87222;0.36727;-4.15737;,
 19.87222;12.64564;-4.15737;,
 19.87222;0.36727;-7.77188;,
 19.87222;12.64564;-7.77188;,
 -19.87222;12.64564;-4.15737;,
 -19.87222;0.36727;-4.15737;,
 -19.87222;12.64564;-7.77188;,
 -19.87222;0.36727;-7.77188;,
 19.87222;12.64564;-15.57674;,
 19.87222;12.64564;-11.83092;,
 19.87222;0.36727;-11.83092;,
 19.87222;0.36727;-15.57674;,
 -19.87222;12.64564;-15.57674;,
 -19.87222;0.36727;-15.57674;,
 -19.87222;0.36727;-11.83092;,
 -19.87222;12.64564;-11.83092;,
 19.87222;12.64564;14.93555;,
 19.87222;0.36727;11.32205;,
 19.87222;12.64564;11.32205;,
 -19.87222;12.64564;14.93555;,
 -19.87222;12.64564;11.32205;,
 -19.87222;0.36727;11.32205;,
 19.87222;12.64564;-15.57674;,
 19.87222;0.36727;-15.57674;,
 16.37052;0.36727;-15.57674;,
 16.37052;12.64564;-15.57674;,
 16.37051;12.64564;14.93555;,
 16.37051;0.36727;14.93555;,
 19.87222;0.36727;14.93555;,
 19.87222;12.64564;14.93555;,
 -19.87222;12.64564;-15.57674;,
 -16.45272;12.64564;-15.57674;,
 -16.45272;0.36727;-15.57674;,
 -19.87222;0.36727;-15.57674;,
 -19.87222;12.64564;14.93555;,
 -19.87222;0.36727;14.93555;,
 -16.45272;0.36727;14.93555;,
 -16.45272;12.64564;14.93555;,
 -12.49158;25.61285;7.80809;,
 -12.49158;27.12290;3.78079;,
 -12.49158;27.72717;-0.32059;,
 -12.49158;0.36727;3.78079;,
 -12.49158;0.36727;7.80809;,
 -12.49158;0.36727;-0.32059;,
 -12.49158;27.10101;-4.15737;,
 -12.49158;25.61285;-7.77188;,
 -12.49158;0.36727;-4.15737;,
 -12.49158;0.36727;-7.77188;,
 -12.49158;23.70523;-11.83091;,
 -12.49158;17.96811;-15.57674;,
 -12.49158;0.36727;-15.57674;,
 -12.49158;0.36727;-11.83092;,
 -12.49158;17.96811;14.93555;,
 -12.49158;23.81462;11.32205;,
 -12.49158;0.36727;11.32205;,
 -12.49158;0.36727;14.93555;,
 -12.49158;12.64564;-15.57674;,
 -12.49158;0.36727;-15.57674;,
 -12.49158;0.36727;14.93555;,
 -12.49158;12.64564;14.93555;,
 -8.79341;25.61285;7.80809;,
 -8.79341;27.12290;3.78079;,
 -8.79341;27.72717;-0.32059;,
 -8.79341;0.36727;3.78079;,
 -8.79341;0.36727;7.80809;,
 -8.79341;0.36727;-0.32059;,
 -8.79341;27.10101;-4.15737;,
 -8.79341;25.61285;-7.77188;,
 -8.79341;0.36727;-4.15737;,
 -8.79341;0.36727;-7.77188;,
 -8.79341;23.70523;-11.83091;,
 -8.79341;17.96811;-15.57674;,
 -8.79341;0.36727;-15.57674;,
 -8.79341;0.36727;-11.83092;,
 -8.79341;17.96811;14.93555;,
 -8.79341;23.81462;11.32205;,
 -8.79341;0.36727;11.32205;,
 -8.79341;0.36727;14.93555;,
 -8.79341;12.64564;-15.57674;,
 -8.79341;0.36727;-15.57674;,
 -8.79341;0.36727;14.93555;,
 -8.79341;12.64564;14.93555;,
 8.46466;25.61285;7.80809;,
 8.46466;27.12290;3.78079;,
 8.46466;27.72717;-0.32059;,
 8.46466;0.36727;3.78079;,
 8.46466;0.36727;7.80809;,
 8.46466;0.36727;-0.32059;,
 8.46466;27.10101;-4.15737;,
 8.46466;25.61285;-7.77188;,
 8.46466;0.36727;-4.15737;,
 8.46466;0.36727;-7.77188;,
 8.46466;23.70523;-11.83091;,
 8.46466;17.96811;-15.57674;,
 8.46466;0.36727;-15.57674;,
 8.46466;0.36727;-11.83092;,
 8.46466;17.96811;14.93555;,
 8.46466;23.81462;11.32205;,
 8.46466;0.36727;11.32205;,
 8.46466;0.36727;14.93555;,
 8.46466;12.64564;-15.57674;,
 8.46466;0.36727;-15.57674;,
 8.46466;0.36727;14.93555;,
 8.46467;12.64564;14.93555;,
 12.16283;25.61285;7.80809;,
 12.16283;27.12290;3.78079;,
 12.16283;27.72717;-0.32059;,
 12.16283;0.36727;3.78079;,
 12.16283;0.36727;7.80809;,
 12.16283;0.36727;-0.32059;,
 12.16283;27.10102;-4.15737;,
 12.16283;25.61285;-7.77188;,
 12.16283;0.36727;-4.15737;,
 12.16283;0.36727;-7.77188;,
 12.16283;23.70523;-11.83091;,
 12.16283;17.96811;-15.57674;,
 12.16283;0.36727;-15.57674;,
 12.16283;0.36727;-11.83092;,
 12.16283;17.96811;14.93555;,
 12.16283;23.81462;11.32205;,
 12.16283;0.36727;11.32205;,
 12.16283;0.36727;14.93555;,
 12.16283;12.64564;-15.57674;,
 12.16283;0.36727;-15.57674;,
 12.16283;0.36727;14.93555;,
 12.16283;12.64564;14.93555;,
 19.87222;17.93814;3.78079;,
 19.87222;27.12290;3.78079;,
 19.87222;25.61285;7.80809;,
 19.87222;17.93814;7.80809;,
 19.87222;17.93814;-0.32059;,
 19.87222;27.72717;-0.32059;,
 -19.87222;17.93814;7.80809;,
 -19.87222;25.61285;7.80809;,
 -19.87222;27.12290;3.78079;,
 -19.87222;17.93814;3.78079;,
 -19.87222;27.72717;-0.32059;,
 -19.87222;17.93814;-0.32059;,
 19.87222;17.93814;-4.15737;,
 19.87222;27.10101;-4.15737;,
 19.87222;17.93814;-7.77187;,
 19.87222;25.61285;-7.77188;,
 -19.87222;27.10101;-4.15737;,
 -19.87222;17.93814;-4.15737;,
 -19.87222;25.61285;-7.77188;,
 -19.87222;17.93814;-7.77187;,
 19.87222;17.93814;-15.57674;,
 19.87222;17.96811;-15.57674;,
 19.87222;23.70523;-11.83091;,
 19.87222;17.93814;-11.83092;,
 -19.87222;17.93814;-11.83092;,
 -19.87222;23.70523;-11.83091;,
 -19.87222;17.96811;-15.57674;,
 -19.87222;17.93814;-15.57674;,
 19.87222;17.93814;11.32205;,
 19.87222;23.81462;11.32205;,
 19.87222;17.93814;14.93555;,
 -19.87222;17.93814;14.93555;,
 -19.87222;23.81462;11.32205;,
 -19.87222;17.93814;11.32205;,
 16.37052;17.93814;-15.57674;,
 16.37052;17.96811;-15.57674;,
 19.87222;17.96811;-15.57674;,
 19.87222;17.93814;-15.57674;,
 19.87222;17.93814;14.93555;,
 19.87222;17.96811;14.93555;,
 16.37051;17.96811;14.93555;,
 16.37051;17.93814;14.93555;,
 -19.87222;17.93814;-15.57674;,
 -19.87222;17.96811;-15.57674;,
 -16.45272;17.96811;-15.57674;,
 -16.45272;17.93814;-15.57674;,
 -16.45272;17.93814;14.93555;,
 -16.45272;17.96811;14.93555;,
 -19.87222;17.96811;14.93555;,
 -19.87222;17.93814;14.93555;,
 -12.49158;17.93814;-15.57674;,
 -12.49158;17.96811;-15.57674;,
 -12.49158;17.93814;14.93555;,
 -12.49158;17.96811;14.93555;,
 -8.79341;17.93814;-15.57674;,
 -8.79341;17.96811;-15.57674;,
 -8.79341;17.93814;14.93555;,
 -8.79341;17.96811;14.93555;,
 8.46467;17.93814;-15.57674;,
 8.46466;17.96811;-15.57674;,
 8.46466;17.93814;14.93555;,
 8.46466;17.96811;14.93555;,
 12.16283;17.93814;-15.57674;,
 12.16283;17.96811;-15.57674;,
 12.16283;17.96811;14.93555;,
 12.16283;17.93814;14.93555;,
 5.35267;17.91732;-16.18104;,
 5.35267;17.91732;-15.36054;,
 5.35267;10.46899;-15.36054;,
 5.35267;10.46899;-16.18104;,
 -5.35267;17.91732;-15.36054;,
 -5.35267;17.91732;-16.18104;,
 -5.35267;10.46899;-16.18104;,
 -5.35267;10.46899;-15.36054;,
 0.00000;8.93683;-16.18104;,
 0.00000;17.91732;-16.18104;,
 5.35267;17.91732;-16.18104;,
 5.35267;10.46899;-16.18104;,
 5.35267;10.46899;-15.36054;,
 5.35267;17.91732;-15.36054;,
 0.00000;17.91732;-15.36054;,
 0.00000;8.93683;-15.36054;,
 0.00000;17.91732;-16.18104;,
 5.35267;17.91732;-16.18104;,
 0.00000;8.93683;-16.18104;,
 5.35267;10.46899;-16.18104;,
 -5.35267;10.46899;-16.18104;,
 -5.35267;17.91732;-16.18104;,
 -5.35267;17.91732;-15.36054;,
 -5.35267;10.46899;-15.36054;,
 -5.35267;17.91732;-16.18104;,
 -5.35267;10.46899;-16.18104;;
 
 212;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;5,4,12,13;,
 4;13,12,14,15;,
 4;10,16,17,11;,
 4;16,18,19,17;,
 4;20,21,22,23;,
 4;21,15,14,22;,
 4;24,25,26,27;,
 4;27,26,19,18;,
 4;28,29,30,31;,
 4;31,30,1,0;,
 4;32,33,34,35;,
 4;33,6,9,34;,
 4;36,37,38,39;,
 4;40,41,37,36;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;48,49,41,40;,
 4;50,51,49,48;,
 4;47,46,52,53;,
 4;53,52,54,55;,
 4;56,57,58,59;,
 4;59,58,51,50;,
 4;60,61,62,63;,
 4;55,54,61,60;,
 4;64,65,66,67;,
 4;39,38,65,64;,
 4;68,69,70,71;,
 4;71,70,43,42;,
 4;72,73,74,75;,
 4;75,74,76,77;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;77,76,84,85;,
 4;85,84,86,87;,
 4;82,88,89,83;,
 4;88,90,91,89;,
 4;92,93,94,95;,
 4;93,87,86,94;,
 4;96,97,98,99;,
 4;99,98,91,90;,
 4;100,35,101,102;,
 4;102,101,73,72;,
 4;103,104,105,69;,
 4;104,78,81,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,36,39;,
 4;123,124,40,36;,
 4;125,126,42,45;,
 4;127,125,45,47;,
 4;124,128,48,40;,
 4;128,129,50,48;,
 4;130,127,47,53;,
 4;131,130,53,55;,
 4;132,133,56,59;,
 4;129,132,59,50;,
 4;134,135,60,63;,
 4;135,131,55,60;,
 4;136,137,64,67;,
 4;137,122,39,64;,
 4;138,139,68,71;,
 4;126,138,71,42;,
 4;140,141,116,115;,
 4;142,143,121,120;,
 4;144,145,123,122;,
 4;145,146,124,123;,
 4;147,148,126,125;,
 4;149,147,125,127;,
 4;146,150,128,124;,
 4;150,151,129,128;,
 4;152,149,127,130;,
 4;153,152,130,131;,
 4;154,155,133,132;,
 4;151,154,132,129;,
 4;156,157,135,134;,
 4;157,153,131,135;,
 4;158,159,137,136;,
 4;159,144,122,137;,
 4;160,161,139,138;,
 4;148,160,138,126;,
 4;162,163,141,140;,
 4;164,165,143,142;,
 4;166,167,145,144;,
 4;167,168,146,145;,
 4;169,170,148,147;,
 4;171,169,147,149;,
 4;168,172,150,146;,
 4;172,173,151,150;,
 4;174,171,149,152;,
 4;175,174,152,153;,
 4;176,177,155,154;,
 4;173,176,154,151;,
 4;178,179,157,156;,
 4;179,175,153,157;,
 4;180,181,159,158;,
 4;181,166,144,159;,
 4;182,183,161,160;,
 4;170,182,160,148;,
 4;184,185,163,162;,
 4;186,187,165,164;,
 4;188,0,3,189;,
 4;188,189,167,166;,
 4;189,3,5,190;,
 4;189,190,168,167;,
 4;191,7,6,192;,
 4;191,192,170,169;,
 4;193,10,7,191;,
 4;193,191,169,171;,
 4;190,5,13,194;,
 4;190,194,172,168;,
 4;194,13,15,195;,
 4;194,195,173,172;,
 4;196,16,10,193;,
 4;196,193,171,174;,
 4;197,18,16,196;,
 4;197,196,174,175;,
 4;198,21,20,199;,
 4;198,199,177,176;,
 4;195,15,21,198;,
 4;195,198,176,173;,
 4;200,24,27,201;,
 4;200,201,179,178;,
 4;201,27,18,197;,
 4;201,197,175,179;,
 4;202,28,31,203;,
 4;202,203,181,180;,
 4;203,31,0,188;,
 4;203,188,166,181;,
 4;204,33,32,205;,
 4;204,205,183,182;,
 4;192,6,33,204;,
 4;192,204,182,170;,
 4;206,109,108,207;,
 4;206,207,185,184;,
 4;208,111,110,209;,
 4;208,209,187,186;,
 4;210,211,212,213;,
 4;210,213,72,75;,
 4;214,215,211,210;,
 4;214,210,75,77;,
 4;216,217,218,219;,
 4;216,219,79,78;,
 4;219,218,220,221;,
 4;219,221,82,79;,
 4;222,223,215,214;,
 4;222,214,77,85;,
 4;224,225,223,222;,
 4;224,222,85,87;,
 4;221,220,226,227;,
 4;221,227,88,82;,
 4;227,226,228,229;,
 4;227,229,90,88;,
 4;230,231,232,233;,
 4;230,233,93,92;,
 4;233,232,225,224;,
 4;233,224,87,93;,
 4;234,235,236,237;,
 4;234,237,96,99;,
 4;229,228,235,234;,
 4;229,234,99,90;,
 4;238,239,29,240;,
 4;238,240,100,102;,
 4;213,212,239,238;,
 4;213,238,102,72;,
 4;241,66,242,243;,
 4;241,243,104,103;,
 4;243,242,217,216;,
 4;243,216,78,104;,
 4;244,245,246,247;,
 4;244,247,106,109;,
 4;248,249,250,251;,
 4;248,251,110,113;,
 4;252,253,254,255;,
 4;252,255,115,114;,
 4;256,257,258,259;,
 4;256,259,118,121;,
 4;260,140,115,255;,
 4;260,255,254,261;,
 4;262,263,257,256;,
 4;262,256,121,143;,
 4;264,162,140,260;,
 4;264,260,261,265;,
 4;266,267,263,262;,
 4;266,262,143,165;,
 4;268,184,162,264;,
 4;268,264,265,269;,
 4;270,271,267,266;,
 4;270,266,165,187;,
 4;244,109,206,272;,
 4;244,272,273,245;,
 4;272,206,184,268;,
 4;272,268,269,273;,
 4;251,250,274,275;,
 4;251,275,209,110;,
 4;275,274,271,270;,
 4;275,270,187,209;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,290,277,293;,
 4;291,294,295,278;,
 4;296,297,285,284;,
 4;291,290,298,299;,
 4;300,280,290,292;,
 4;283,301,294,291;;
 
 MeshMaterialList {
  3;
  212;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
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
  1;;
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.674510;0.000000;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  57;
  0.000000;0.285194;-0.958470;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.273277;0.961935;,
  0.000000;0.914768;0.403980;,
  0.000000;0.914768;0.403980;,
  0.000000;0.999970;-0.007746;,
  0.000000;0.999970;-0.007746;,
  -0.000000;0.915136;-0.403145;,
  0.000000;0.915136;-0.403145;,
  0.000000;0.968290;0.249831;,
  -0.000000;0.962107;-0.272673;,
  0.000000;0.962107;-0.272673;,
  -0.000000;0.754532;-0.656264;,
  0.000000;0.754532;-0.656264;,
  0.000000;0.735021;0.678044;,
  0.000000;0.735021;0.678044;,
  0.000000;0.999970;-0.007746;,
  0.000000;0.915136;-0.403146;,
  0.000001;0.962107;-0.272673;,
  0.000000;0.754532;-0.656264;,
  0.000000;0.735021;0.678044;,
  0.000000;0.273277;0.961935;,
  0.000000;0.999970;-0.007746;,
  -0.000000;0.915136;-0.403145;,
  -0.000000;0.962107;-0.272673;,
  -0.000000;0.754532;-0.656264;,
  0.000000;0.735021;0.678044;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.285194;-0.958470;,
  0.000000;0.914768;0.403980;,
  0.000000;0.999970;-0.007746;,
  0.000000;0.915136;-0.403145;,
  0.000000;0.962107;-0.272673;,
  0.000000;0.754532;-0.656264;,
  0.000000;0.915136;-0.403145;,
  0.000000;0.962107;-0.272673;,
  0.000000;0.754532;-0.656264;,
  -0.000000;0.999970;-0.007746;,
  -0.000000;0.915136;-0.403146;,
  -0.000001;0.962107;-0.272673;,
  -0.000000;0.754532;-0.656264;,
  -0.000000;0.999970;-0.007745;,
  -0.000000;0.915136;-0.403146;,
  0.000000;0.968290;0.249831;,
  -0.000000;0.962107;-0.272673;,
  -0.000000;0.754532;-0.656264;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.275190;-0.961390;-0.000000;,
  -0.275190;-0.961390;0.000000;;
  212;
  4;4,4,9,9;,
  4;9,9,6,16;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;16,6,11,18;,
  4;18,11,8,17;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,19,13,0;,
  4;19,17,8,13;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,14,20;,
  4;20,14,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;9,9,3,3;,
  4;22,5,9,9;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;24,10,5,22;,
  4;23,7,10,24;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,12,25;,
  4;25,12,7,23;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;26,15,2,21;,
  4;3,3,15,26;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;32,9,9,3;,
  4;9,33,22,9;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;33,35,24,22;,
  4;35,34,23,24;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;36,31,0,25;,
  4;34,36,25,23;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;21,26,26,21;,
  4;26,32,3,26;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;4,9,9,32;,
  4;9,33,33,9;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;33,38,35,33;,
  4;38,37,34,35;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;39,31,31,36;,
  4;37,39,36,34;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;21,20,26,21;,
  4;20,4,32,26;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;4,9,9,4;,
  4;9,40,33,9;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;40,42,38,33;,
  4;42,41,37,38;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;43,31,31,39;,
  4;41,43,39,37;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;21,20,20,21;,
  4;20,4,4,20;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;4,4,9,46;,
  4;4,46,9,4;,
  4;46,9,16,44;,
  4;46,44,40,9;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;44,16,18,47;,
  4;44,47,42,40;,
  4;47,18,17,45;,
  4;47,45,41,42;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;48,19,0,0;,
  4;48,0,31,43;,
  4;45,17,19,48;,
  4;45,48,43,41;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,20,20;,
  4;2,20,20,21;,
  4;20,20,4,4;,
  4;20,4,4,20;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;29,0,0,29;,
  4;29,29,29,29;,
  4;30,2,2,30;,
  4;30,30,30,30;,
  4;29,0,0,29;,
  4;29,29,29,29;,
  4;30,21,2,30;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;29,29,0,31;,
  4;30,21,21,30;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;29,29,31,31;,
  4;30,21,21,30;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;29,29,31,31;,
  4;30,21,21,30;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;29,29,0,0;,
  4;29,29,29,29;,
  4;29,29,31,0;,
  4;30,2,2,30;,
  4;30,30,30,30;,
  4;30,2,21,30;,
  4;30,30,30,30;,
  4;51,51,51,51;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,55,55;,
  4;50,50,50,50;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;56,56,54,54;;
 }
 MeshTextureCoords {
  302;
  0.870539;0.233594;,
  1.000000;0.233594;,
  1.000000;0.365583;,
  0.870539;0.365583;,
  1.000000;0.500000;,
  0.870539;0.500000;,
  0.870539;0.766406;,
  0.870539;0.634417;,
  1.000000;0.634417;,
  1.000000;0.766406;,
  0.870539;0.500000;,
  1.000000;0.500000;,
  1.000000;0.625745;,
  0.870539;0.625745;,
  1.000000;0.744206;,
  0.870539;0.744206;,
  0.870539;0.374255;,
  1.000000;0.374255;,
  0.870539;0.255794;,
  1.000000;0.255794;,
  0.870539;1.000000;,
  0.870539;0.877236;,
  1.000000;0.877236;,
  1.000000;1.000000;,
  0.870539;0.000000;,
  1.000000;0.000000;,
  1.000000;0.122764;,
  0.870539;0.122764;,
  0.870539;0.000000;,
  1.000000;0.000000;,
  1.000000;0.118428;,
  0.870539;0.118428;,
  0.870539;1.000000;,
  0.870539;0.881572;,
  1.000000;0.881572;,
  1.000000;1.000000;,
  0.112918;0.365583;,
  0.000000;0.365583;,
  0.000000;0.233594;,
  0.112918;0.233594;,
  0.112918;0.500000;,
  0.000000;0.500000;,
  0.112918;0.766406;,
  0.000000;0.766406;,
  0.000000;0.634417;,
  0.112918;0.634417;,
  0.000000;0.500000;,
  0.112918;0.500000;,
  0.112918;0.625745;,
  0.000000;0.625745;,
  0.112918;0.744206;,
  0.000000;0.744206;,
  0.000000;0.374255;,
  0.112918;0.374255;,
  0.000000;0.255794;,
  0.112918;0.255794;,
  0.112918;1.000000;,
  0.000000;1.000000;,
  0.000000;0.877236;,
  0.112918;0.877236;,
  0.112918;0.122764;,
  0.000000;0.122764;,
  0.000000;0.000000;,
  0.112918;0.000000;,
  0.112918;0.118428;,
  0.000000;0.118428;,
  0.000000;0.000000;,
  0.112918;0.000000;,
  0.112918;1.000000;,
  0.000000;1.000000;,
  0.000000;0.881572;,
  0.112918;0.881572;,
  0.766406;0.513643;,
  0.766406;1.000000;,
  0.634417;1.000000;,
  0.634417;0.541092;,
  0.500000;1.000000;,
  0.500000;0.551228;,
  0.233594;0.513643;,
  0.365583;0.541092;,
  0.365583;1.000000;,
  0.233594;1.000000;,
  0.500000;0.551228;,
  0.500000;1.000000;,
  0.374255;1.000000;,
  0.374255;0.540716;,
  0.255794;1.000000;,
  0.255794;0.513643;,
  0.625745;0.540716;,
  0.625745;1.000000;,
  0.744206;0.513643;,
  0.744206;1.000000;,
  0.000000;0.302399;,
  0.122764;0.473888;,
  0.122764;1.000000;,
  0.000000;1.000000;,
  1.000000;0.302399;,
  1.000000;1.000000;,
  0.877236;1.000000;,
  0.877236;0.473888;,
  1.000000;0.302399;,
  0.881572;1.000000;,
  0.881572;0.476343;,
  0.000000;0.302399;,
  0.118428;0.476343;,
  0.118428;1.000000;,
  1.000000;0.302399;,
  1.000000;1.000000;,
  0.870539;1.000000;,
  0.870539;0.302399;,
  0.129461;0.302399;,
  0.129461;1.000000;,
  0.000000;1.000000;,
  0.000000;0.302399;,
  0.000000;0.302399;,
  0.112918;0.302399;,
  0.112918;1.000000;,
  0.000000;1.000000;,
  1.000000;0.302399;,
  1.000000;1.000000;,
  0.887082;1.000000;,
  0.887082;0.302399;,
  0.177432;0.233594;,
  0.177432;0.365583;,
  0.177432;0.500000;,
  0.177432;0.634417;,
  0.177432;0.766406;,
  0.177432;0.500000;,
  0.177432;0.625745;,
  0.177432;0.744206;,
  0.177432;0.374255;,
  0.177432;0.255794;,
  0.177432;0.877236;,
  0.177432;1.000000;,
  0.177432;0.000000;,
  0.177432;0.122764;,
  0.177432;0.000000;,
  0.177432;0.118428;,
  0.177432;0.881572;,
  0.177432;1.000000;,
  0.177432;0.302399;,
  0.177432;1.000000;,
  0.822568;1.000000;,
  0.822568;0.302399;,
  0.247735;0.233594;,
  0.247735;0.365583;,
  0.247735;0.500000;,
  0.247735;0.634417;,
  0.247735;0.766406;,
  0.247735;0.500000;,
  0.247735;0.625745;,
  0.247735;0.744206;,
  0.247735;0.374255;,
  0.247735;0.255794;,
  0.247735;0.877236;,
  0.247735;1.000000;,
  0.247735;0.000000;,
  0.247735;0.122764;,
  0.247735;0.000000;,
  0.247735;0.118428;,
  0.247735;0.881572;,
  0.247735;1.000000;,
  0.247735;0.302399;,
  0.247735;1.000000;,
  0.752265;1.000000;,
  0.752265;0.302399;,
  0.712977;0.233594;,
  0.712977;0.365583;,
  0.712977;0.500000;,
  0.712977;0.634417;,
  0.712977;0.766406;,
  0.712977;0.500000;,
  0.712977;0.625745;,
  0.712977;0.744206;,
  0.712977;0.374255;,
  0.712977;0.255794;,
  0.712977;0.877236;,
  0.712977;1.000000;,
  0.712977;0.000000;,
  0.712977;0.122764;,
  0.712977;0.000000;,
  0.712977;0.118428;,
  0.712977;0.881572;,
  0.712977;1.000000;,
  0.712977;0.302399;,
  0.712977;1.000000;,
  0.287023;1.000000;,
  0.287023;0.302399;,
  0.793619;0.233594;,
  0.793619;0.365583;,
  0.793619;0.500000;,
  0.793619;0.634417;,
  0.793619;0.766407;,
  0.793619;0.500000;,
  0.793619;0.625745;,
  0.793619;0.744206;,
  0.793619;0.374255;,
  0.793619;0.255794;,
  0.793619;0.877236;,
  0.793619;1.000000;,
  0.793619;0.000000;,
  0.793619;0.122764;,
  0.793619;0.000000;,
  0.793619;0.118428;,
  0.793619;0.881572;,
  0.793619;1.000000;,
  0.793619;0.302399;,
  0.793619;1.000000;,
  0.206381;1.000000;,
  0.206381;0.302399;,
  0.634417;0.343284;,
  0.634417;0.000000;,
  0.766406;0.000000;,
  0.766406;0.304003;,
  0.500000;0.357788;,
  0.500000;0.000000;,
  0.233594;0.304003;,
  0.233594;0.000000;,
  0.365583;0.000000;,
  0.365583;0.343284;,
  0.500000;0.000000;,
  0.500000;0.357788;,
  0.374255;0.342746;,
  0.374255;0.000000;,
  0.255794;0.304003;,
  0.255794;0.000000;,
  0.625745;0.000000;,
  0.625745;0.342746;,
  0.744206;0.000000;,
  0.744206;0.304003;,
  0.000000;0.001705;,
  0.000000;0.000000;,
  0.122764;0.000000;,
  0.122764;0.247113;,
  0.877236;0.247113;,
  0.877236;0.000000;,
  1.000000;0.000000;,
  1.000000;0.001705;,
  0.881572;0.250625;,
  0.881572;0.000000;,
  1.000000;0.001705;,
  0.000000;0.001705;,
  0.118428;0.000000;,
  0.118428;0.250625;,
  0.870539;0.001705;,
  0.870539;0.000000;,
  1.000000;0.000000;,
  1.000000;0.001705;,
  0.000000;0.001705;,
  0.000000;0.000000;,
  0.129461;0.000000;,
  0.129461;0.001705;,
  0.000000;0.001705;,
  0.000000;0.000000;,
  0.112918;0.000000;,
  0.112918;0.001705;,
  0.887082;0.001705;,
  0.887082;0.000000;,
  1.000000;0.000000;,
  1.000000;0.001705;,
  0.177432;0.001705;,
  0.177432;0.000000;,
  0.822568;0.001705;,
  0.822568;0.000000;,
  0.247735;0.001705;,
  0.247735;0.000000;,
  0.752265;0.001705;,
  0.752265;0.000000;,
  0.712977;0.001705;,
  0.712977;0.000000;,
  0.287023;0.001705;,
  0.287023;0.000000;,
  0.793619;0.001705;,
  0.793619;0.000000;,
  0.206381;0.000000;,
  0.206381;0.001705;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;;
 }
}
