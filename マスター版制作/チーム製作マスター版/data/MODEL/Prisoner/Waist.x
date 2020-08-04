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
 233;
 0.31475;2.42740;5.11511;,
 0.31475;2.04135;5.73772;,
 4.48155;2.42740;5.11511;,
 4.48155;2.04135;5.73772;,
 4.48155;5.69425;-2.79721;,
 0.31475;5.69425;-2.79721;,
 4.48155;5.69425;-0.46425;,
 0.31475;5.69425;-0.46425;,
 0.31475;2.04135;-5.67237;,
 0.31475;2.42740;-5.04976;,
 4.48155;2.04135;-5.67237;,
 4.48155;2.42740;-5.04976;,
 3.67960;-5.77520;-0.31474;,
 0.25020;-4.81850;-0.31474;,
 3.67960;-5.77520;-1.94625;,
 0.25020;-4.81850;-1.94625;,
 7.52875;2.42740;-0.46425;,
 8.12500;2.04135;-0.46425;,
 7.52875;2.42740;-2.79721;,
 8.12500;2.04135;-2.79721;,
 -7.32880;2.42740;-2.79721;,
 -7.92515;2.04135;-2.79721;,
 -7.32880;2.42740;-0.46425;,
 -7.92515;2.04135;-0.46425;,
 4.51750;-2.22635;5.73772;,
 0.31475;-2.22635;5.73772;,
 4.51750;-3.25585;5.73772;,
 0.31475;-3.25585;5.73772;,
 8.82390;-2.22635;-2.79721;,
 8.82390;-2.22635;-0.46425;,
 8.82390;-3.25585;-2.79721;,
 8.82390;-3.25585;-0.46425;,
 4.51750;-3.25585;-5.67237;,
 0.31475;-3.25585;-5.67237;,
 4.51750;-2.22635;-5.67237;,
 0.31475;-2.22635;-5.67237;,
 -8.62400;-2.22635;-0.46425;,
 -8.62400;-2.22635;-2.79721;,
 -8.62400;-3.25585;-0.46425;,
 -8.62400;-3.25585;-2.79721;,
 0.31475;5.69425;-5.04976;,
 4.48155;5.69425;-5.04976;,
 7.52875;5.69425;-0.46425;,
 7.52875;5.69425;-2.79721;,
 0.31475;5.69425;5.11511;,
 4.48155;5.69425;5.11511;,
 -7.32880;5.69425;-2.79721;,
 -7.32880;5.69425;-0.46425;,
 0.31475;-1.16415;-5.67237;,
 0.31475;0.32130;-5.67237;,
 4.51750;-1.16415;-5.67237;,
 4.51750;0.32130;-5.67237;,
 8.82390;0.32130;-2.79721;,
 8.82390;0.32130;-0.46425;,
 8.82390;-1.16415;-2.79721;,
 8.82390;-1.16415;-0.46425;,
 4.51750;0.32130;5.73772;,
 0.31475;0.32130;5.73772;,
 4.51750;-1.16415;5.73772;,
 0.31475;-1.16415;5.73772;,
 -8.62400;0.32130;-0.46425;,
 -8.62400;0.32130;-2.79721;,
 -8.62400;-1.16415;-0.46425;,
 -8.62400;-1.16415;-2.79721;,
 -6.20290;-5.77520;-1.94625;,
 -3.33455;-5.77520;-1.94625;,
 -6.20290;-5.77520;-0.31474;,
 -3.33455;-5.77520;-0.31474;,
 -6.96880;-2.22635;-5.04976;,
 -4.05515;-2.22635;-5.67237;,
 -6.96880;-3.25585;-5.04976;,
 -4.05515;-3.25585;-5.67237;,
 -6.96880;0.32130;-5.04976;,
 -4.05515;0.32130;-5.67237;,
 -6.96880;-1.16415;-5.04976;,
 -4.05515;-1.16415;-5.67237;,
 -5.65285;2.42740;-5.04976;,
 -4.07400;2.42740;-5.04976;,
 -6.26995;2.04135;-5.04976;,
 -4.07400;2.04135;-5.67237;,
 -5.65285;5.69425;-5.04976;,
 -4.07400;5.69425;-5.04976;,
 -7.32880;5.69425;-0.46425;,
 -4.07400;5.69425;-0.46425;,
 -7.32880;5.69425;-2.79721;,
 -4.07400;5.69425;-2.79721;,
 -5.65285;2.42740;5.11511;,
 -4.07400;2.42740;5.11511;,
 -5.65285;5.69425;5.11511;,
 -4.07400;5.69425;5.11511;,
 -4.07400;2.04135;5.73772;,
 -6.26995;2.04135;5.11511;,
 -6.96880;-1.16415;5.11511;,
 -4.05515;-1.16415;5.73772;,
 -6.96880;0.32130;5.11511;,
 -4.05515;0.32130;5.73772;,
 -6.96880;-3.25585;5.11511;,
 -4.05515;-3.25585;5.73772;,
 -6.96880;-2.22635;5.11511;,
 -4.05515;-2.22635;5.73772;,
 7.16865;-1.16415;-5.04976;,
 7.16865;0.32130;-5.04976;,
 7.16865;-3.25585;-5.04976;,
 7.16865;-2.22635;-5.04976;,
 6.40280;-5.77520;-0.31474;,
 6.40280;-5.77520;-1.94625;,
 7.16865;-2.22635;5.11511;,
 7.16865;-3.25585;5.11511;,
 7.16865;0.32130;5.11511;,
 7.16865;-1.16415;5.11511;,
 6.46980;2.04135;5.11511;,
 5.85270;2.42740;5.11511;,
 5.85270;5.69425;5.11511;,
 7.52875;5.69425;-2.79721;,
 7.52875;5.69425;-0.46425;,
 5.85270;2.42740;-5.04976;,
 5.85270;5.69425;-5.04976;,
 6.46980;2.04135;-5.04976;,
 -7.32880;5.69425;2.11725;,
 -4.07400;5.69425;2.11725;,
 0.31475;5.69425;2.11725;,
 4.48155;5.69425;2.11725;,
 7.52875;5.69425;2.11725;,
 7.52875;5.69425;2.11725;,
 7.52875;2.42740;2.11725;,
 8.12500;2.04135;2.11725;,
 8.82390;0.32130;2.11725;,
 8.82390;-1.16415;2.11725;,
 8.82390;-2.22635;2.11725;,
 8.82390;-3.25585;2.11725;,
 6.40280;-5.77520;1.49036;,
 3.67960;-5.77520;1.49036;,
 0.25020;-4.81850;1.49036;,
 -3.33455;-5.77520;1.49036;,
 -6.20290;-5.77520;1.49040;,
 -8.62400;-2.22635;2.11725;,
 -8.62400;-3.25585;2.11725;,
 -8.62400;0.32130;2.11725;,
 -8.62400;-1.16415;2.11725;,
 -7.32880;2.42740;2.11725;,
 -7.92515;2.04135;2.11725;,
 -7.32880;5.69425;2.11725;,
 3.67960;-5.77520;3.58675;,
 4.63850;-5.77520;3.58675;,
 0.25020;-4.81850;3.58675;,
 -3.33455;-5.77520;3.58675;,
 -4.43865;-5.77520;3.58675;,
 -3.33455;-5.77520;-3.52140;,
 -4.43865;-5.77520;-3.52140;,
 0.25020;-4.81850;-3.52140;,
 3.67960;-5.77520;-3.52140;,
 4.63850;-5.77520;-3.52140;,
 7.16865;-2.22635;-5.04976;,
 7.16865;-3.25585;-5.04976;,
 7.16865;0.32130;-5.04976;,
 7.16865;-1.16415;-5.04976;,
 6.46980;2.04135;-5.04976;,
 5.85270;2.42740;-5.04976;,
 5.85270;5.69425;-5.04976;,
 -5.65285;2.42740;-5.04976;,
 -5.65285;5.69425;-5.04976;,
 -6.26995;2.04135;-5.04976;,
 -6.96880;-1.16415;-5.04976;,
 -6.96880;0.32130;-5.04976;,
 -6.96880;-3.25585;-5.04976;,
 -6.96880;-2.22635;-5.04976;,
 -4.06655;-4.06080;5.73772;,
 -4.06390;-3.87420;5.73772;,
 -6.54750;-4.06080;5.11511;,
 -6.64515;-3.87420;5.11511;,
 0.31475;-3.87420;5.73772;,
 0.31475;-4.06080;5.73772;,
 4.50080;-3.87420;5.73772;,
 4.49580;-4.06080;5.73772;,
 6.84500;-3.87420;5.11511;,
 6.74735;-4.06080;5.11511;,
 8.40265;-4.06080;2.11725;,
 8.50030;-3.87420;2.11725;,
 8.50030;-3.87420;-0.46425;,
 8.40265;-4.06080;-0.46425;,
 8.50030;-3.87420;-2.79721;,
 8.40265;-4.06080;-2.79721;,
 6.84500;-3.87420;-5.04976;,
 6.74735;-4.06080;-5.04976;,
 4.49580;-4.06080;-5.67237;,
 4.50080;-3.87420;-5.67237;,
 6.74735;-4.06080;-5.04976;,
 6.84500;-3.87420;-5.04976;,
 0.31475;-4.06080;-5.67237;,
 0.31475;-3.87420;-5.67237;,
 -4.06655;-4.06080;-5.67237;,
 -4.06390;-3.87420;-5.67237;,
 -6.64515;-3.87420;-5.04976;,
 -6.54750;-4.06080;-5.04976;,
 -6.54750;-4.06080;-5.04976;,
 -8.20270;-4.06080;-2.79721;,
 -6.64515;-3.87420;-5.04976;,
 -8.30040;-3.87420;-2.79721;,
 -8.30040;-3.87420;-0.46425;,
 -8.20270;-4.06080;-0.46425;,
 -8.30040;-3.87420;2.11725;,
 -8.20270;-4.06080;2.11725;,
 -4.06995;-4.30280;5.73772;,
 -6.42080;-4.30280;5.11511;,
 0.31475;-4.30280;5.73772;,
 4.48930;-4.30280;5.73772;,
 6.62075;-4.30280;5.11511;,
 8.27600;-4.30280;2.11725;,
 8.27600;-4.30280;-0.46425;,
 8.27600;-4.30280;-2.79721;,
 6.62075;-4.30280;-5.04976;,
 4.48930;-4.30280;-5.67237;,
 6.62075;-4.30280;-5.04976;,
 0.31475;-4.30280;-5.67237;,
 -4.06995;-4.30280;-5.67237;,
 -6.42080;-4.30280;-5.04976;,
 -6.42080;-4.30280;-5.04976;,
 -8.07610;-4.30280;-2.79721;,
 -8.07610;-4.30280;-0.46425;,
 -8.07610;-4.30280;2.11725;,
 -4.43865;-5.77520;3.58675;,
 -3.33455;-5.77520;3.58675;,
 0.25020;-4.81850;3.58675;,
 3.67960;-5.77520;3.58675;,
 4.63850;-5.77520;3.58675;,
 6.40280;-5.77520;1.49036;,
 6.40280;-5.77520;-0.31474;,
 6.40280;-5.77520;-1.94625;,
 4.63850;-5.77520;-3.52140;,
 -6.20290;-5.77520;-1.94625;,
 -4.43865;-5.77520;-3.52140;,
 -6.20290;-5.77520;-0.31474;,
 -6.20290;-5.77520;1.49040;;
 
 384;
 3;0,1,2;,
 3;2,1,3;,
 3;4,5,6;,
 3;6,5,7;,
 3;8,9,10;,
 3;10,9,11;,
 3;12,13,14;,
 3;14,13,15;,
 3;16,17,18;,
 3;18,17,19;,
 3;20,21,22;,
 3;22,21,23;,
 3;24,25,26;,
 3;26,25,27;,
 3;28,29,30;,
 3;30,29,31;,
 3;32,33,34;,
 3;34,33,35;,
 3;36,37,38;,
 3;38,37,39;,
 3;9,40,11;,
 3;11,40,41;,
 3;42,16,43;,
 3;43,16,18;,
 3;44,0,45;,
 3;45,0,2;,
 3;46,20,47;,
 3;47,20,22;,
 3;48,49,50;,
 3;50,49,51;,
 3;52,53,54;,
 3;54,53,55;,
 3;56,57,58;,
 3;58,57,59;,
 3;60,61,62;,
 3;62,61,63;,
 3;64,65,66;,
 3;66,65,67;,
 3;68,69,70;,
 3;70,69,71;,
 3;72,73,74;,
 3;74,73,75;,
 3;76,77,78;,
 3;78,77,79;,
 3;80,81,76;,
 3;76,81,77;,
 3;82,83,84;,
 3;84,83,85;,
 3;86,87,88;,
 3;88,87,89;,
 3;90,87,91;,
 3;91,87,86;,
 3;92,93,94;,
 3;94,93,95;,
 3;96,97,98;,
 3;98,97,99;,
 3;50,51,100;,
 3;100,51,101;,
 3;102,32,103;,
 3;103,32,34;,
 3;104,12,105;,
 3;105,12,14;,
 3;106,24,107;,
 3;107,24,26;,
 3;108,56,109;,
 3;109,56,58;,
 3;110,111,3;,
 3;2,3,111;,
 3;45,2,112;,
 3;112,2,111;,
 3;113,4,114;,
 3;114,4,6;,
 3;11,41,115;,
 3;115,41,116;,
 3;117,10,115;,
 3;10,11,115;,
 3;75,73,48;,
 3;48,73,49;,
 3;33,71,35;,
 3;35,71,69;,
 3;13,67,15;,
 3;15,67,65;,
 3;25,99,27;,
 3;27,99,97;,
 3;57,95,59;,
 3;59,95,93;,
 3;87,90,0;,
 3;0,90,1;,
 3;89,87,44;,
 3;44,87,0;,
 3;5,85,7;,
 3;7,85,83;,
 3;77,81,9;,
 3;9,81,40;,
 3;79,77,8;,
 3;8,77,9;,
 3;118,119,82;,
 3;82,119,83;,
 3;7,83,120;,
 3;120,83,119;,
 3;6,7,121;,
 3;121,7,120;,
 3;114,6,122;,
 3;122,6,121;,
 3;123,124,42;,
 3;42,124,16;,
 3;124,125,16;,
 3;16,125,17;,
 3;53,126,55;,
 3;55,126,127;,
 3;29,128,31;,
 3;31,128,129;,
 3;130,131,104;,
 3;104,131,12;,
 3;131,132,12;,
 3;12,132,13;,
 3;132,133,13;,
 3;13,133,67;,
 3;66,67,134;,
 3;134,67,133;,
 3;135,36,136;,
 3;136,36,38;,
 3;137,60,138;,
 3;138,60,62;,
 3;22,23,139;,
 3;139,23,140;,
 3;47,22,141;,
 3;141,22,139;,
 3;89,119,88;,
 3;88,119,118;,
 3;120,119,44;,
 3;44,119,89;,
 3;121,120,45;,
 3;45,120,44;,
 3;122,121,112;,
 3;112,121,45;,
 3;111,124,112;,
 3;112,124,123;,
 3;125,124,110;,
 3;110,124,111;,
 3;109,127,108;,
 3;108,127,126;,
 3;107,129,106;,
 3;106,129,128;,
 3;142,131,143;,
 3;143,131,130;,
 3;144,132,142;,
 3;142,132,131;,
 3;145,133,144;,
 3;144,133,132;,
 3;134,133,146;,
 3;146,133,145;,
 3;98,135,96;,
 3;96,135,136;,
 3;94,137,92;,
 3;92,137,138;,
 3;140,91,139;,
 3;139,91,86;,
 3;141,139,88;,
 3;88,139,86;,
 3;147,65,148;,
 3;148,65,64;,
 3;15,65,149;,
 3;149,65,147;,
 3;14,15,150;,
 3;150,15,149;,
 3;105,14,151;,
 3;151,14,150;,
 3;152,28,153;,
 3;153,28,30;,
 3;154,52,155;,
 3;155,52,54;,
 3;19,156,18;,
 3;18,156,157;,
 3;43,18,158;,
 3;158,18,157;,
 3;41,4,116;,
 3;116,4,113;,
 3;40,5,41;,
 3;41,5,4;,
 3;81,85,40;,
 3;40,85,5;,
 3;84,85,80;,
 3;80,85,81;,
 3;159,20,160;,
 3;160,20,46;,
 3;21,20,161;,
 3;161,20,159;,
 3;162,63,163;,
 3;163,63,61;,
 3;164,39,165;,
 3;165,39,37;,
 3;166,167,168;,
 3;168,167,169;,
 3;170,167,171;,
 3;171,167,166;,
 3;172,170,173;,
 3;173,170,171;,
 3;174,172,175;,
 3;175,172,173;,
 3;175,176,174;,
 3;174,176,177;,
 3;178,177,179;,
 3;179,177,176;,
 3;180,178,181;,
 3;181,178,179;,
 3;180,181,182;,
 3;182,181,183;,
 3;184,185,186;,
 3;186,185,187;,
 3;188,189,184;,
 3;184,189,185;,
 3;190,191,188;,
 3;188,191,189;,
 3;192,191,193;,
 3;193,191,190;,
 3;194,195,196;,
 3;196,195,197;,
 3;198,197,199;,
 3;199,197,195;,
 3;200,198,201;,
 3;201,198,199;,
 3;200,201,169;,
 3;169,201,168;,
 3;52,154,19;,
 3;19,154,156;,
 3;17,53,19;,
 3;19,53,52;,
 3;125,126,17;,
 3;17,126,53;,
 3;126,125,108;,
 3;108,125,110;,
 3;3,56,110;,
 3;110,56,108;,
 3;1,57,3;,
 3;3,57,56;,
 3;90,95,1;,
 3;1,95,57;,
 3;94,95,91;,
 3;91,95,90;,
 3;137,94,140;,
 3;140,94,91;,
 3;23,60,140;,
 3;140,60,137;,
 3;21,61,23;,
 3;23,61,60;,
 3;61,21,163;,
 3;163,21,161;,
 3;79,73,78;,
 3;78,73,72;,
 3;49,73,8;,
 3;8,73,79;,
 3;51,49,10;,
 3;10,49,8;,
 3;101,51,117;,
 3;117,51,10;,
 3;74,75,68;,
 3;68,75,69;,
 3;35,69,48;,
 3;48,69,75;,
 3;34,35,50;,
 3;50,35,48;,
 3;103,34,100;,
 3;100,34,50;,
 3;54,28,155;,
 3;155,28,152;,
 3;55,29,54;,
 3;54,29,28;,
 3;127,128,55;,
 3;55,128,29;,
 3;106,128,109;,
 3;109,128,127;,
 3;58,24,109;,
 3;109,24,106;,
 3;59,25,58;,
 3;58,25,24;,
 3;93,99,59;,
 3;59,99,25;,
 3;98,99,92;,
 3;92,99,93;,
 3;138,135,92;,
 3;92,135,98;,
 3;62,36,138;,
 3;138,36,135;,
 3;63,37,62;,
 3;62,37,36;,
 3;165,37,162;,
 3;162,37,63;,
 3;202,166,203;,
 3;203,166,168;,
 3;171,166,204;,
 3;204,166,202;,
 3;173,171,205;,
 3;205,171,204;,
 3;175,173,206;,
 3;206,173,205;,
 3;206,207,175;,
 3;175,207,176;,
 3;179,176,208;,
 3;208,176,207;,
 3;181,179,209;,
 3;209,179,208;,
 3;181,209,183;,
 3;183,209,210;,
 3;211,184,212;,
 3;212,184,186;,
 3;213,188,211;,
 3;211,188,184;,
 3;214,190,213;,
 3;213,190,188;,
 3;193,190,215;,
 3;215,190,214;,
 3;216,217,194;,
 3;194,217,195;,
 3;199,195,218;,
 3;218,195,217;,
 3;201,199,219;,
 3;219,199,218;,
 3;201,219,168;,
 3;168,219,203;,
 3;220,221,203;,
 3;203,221,202;,
 3;202,221,204;,
 3;204,221,222;,
 3;205,204,223;,
 3;223,204,222;,
 3;205,223,206;,
 3;206,223,224;,
 3;225,207,224;,
 3;224,207,206;,
 3;207,225,208;,
 3;208,225,226;,
 3;209,208,227;,
 3;227,208,226;,
 3;210,209,228;,
 3;228,209,227;,
 3;211,212,150;,
 3;150,212,151;,
 3;149,213,150;,
 3;150,213,211;,
 3;214,213,147;,
 3;147,213,149;,
 3;214,147,215;,
 3;215,147,148;,
 3;229,217,230;,
 3;230,217,216;,
 3;217,229,218;,
 3;218,229,231;,
 3;219,218,232;,
 3;232,218,231;,
 3;203,219,220;,
 3;220,219,232;,
 3;27,97,170;,
 3;170,97,167;,
 3;167,97,169;,
 3;169,97,96;,
 3;136,200,96;,
 3;96,200,169;,
 3;136,38,200;,
 3;200,38,198;,
 3;38,39,198;,
 3;198,39,197;,
 3;196,197,164;,
 3;164,197,39;,
 3;70,71,192;,
 3;192,71,191;,
 3;191,71,189;,
 3;189,71,33;,
 3;189,33,185;,
 3;185,33,32;,
 3;185,32,187;,
 3;187,32,102;,
 3;30,180,153;,
 3;153,180,182;,
 3;30,31,180;,
 3;180,31,178;,
 3;31,129,178;,
 3;178,129,177;,
 3;174,177,107;,
 3;107,177,129;,
 3;107,26,174;,
 3;174,26,172;,
 3;26,27,172;,
 3;172,27,170;;
 
 MeshMaterialList {
  3;
  384;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.238400;0.269600;0.156800;1.000000;;
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
   0.693600;0.508000;0.360800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  166;
  -0.198972;-0.936531;0.288653;,
  0.198969;-0.936532;0.288650;,
  -0.000000;0.000000;1.000000;,
  -0.590350;0.000000;-0.807147;,
  0.590334;0.000000;-0.807159;,
  -0.175096;-0.934210;-0.310793;,
  0.175094;-0.934211;-0.310792;,
  -0.422435;0.489065;0.763128;,
  0.503401;0.471432;0.724113;,
  0.474991;0.446982;-0.758017;,
  -0.397585;0.465533;-0.790699;,
  -0.217701;0.000000;-0.976016;,
  0.308918;0.408436;-0.858924;,
  0.399280;0.506355;0.764316;,
  -0.542831;0.000000;-0.839842;,
  0.551256;0.000000;-0.834336;,
  0.552323;0.000000;0.833630;,
  -0.646878;0.000000;0.762593;,
  0.049408;-0.994355;0.093901;,
  0.049408;-0.994355;-0.093901;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.486327;-0.873777;,
  0.000000;0.486327;-0.873777;,
  0.000000;0.486327;0.873777;,
  0.000000;0.486327;0.873777;,
  0.091780;0.482234;-0.871222;,
  0.076661;0.000000;-0.997057;,
  -0.098106;-0.947389;-0.304678;,
  -0.098106;-0.947389;0.304678;,
  0.076661;0.000000;0.997057;,
  0.106299;0.399601;0.910505;,
  0.000000;0.386674;-0.922217;,
  -0.120969;0.485391;-0.865888;,
  -0.126051;0.000000;-0.992024;,
  0.065246;-0.933246;-0.353264;,
  0.065246;-0.933246;0.353264;,
  -0.126051;0.000000;0.992024;,
  -0.096159;0.580172;0.808798;,
  -0.023524;0.269105;0.962824;,
  -0.028226;0.485242;-0.873924;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.878490;0.477760;0.000000;,
  0.770560;0.637367;0.000000;,
  0.260943;-0.965354;-0.000000;,
  -0.135608;-0.990763;0.000000;,
  -0.005626;-0.999984;0.000000;,
  0.130032;-0.991510;-0.000000;,
  -0.260943;-0.965354;0.000000;,
  -0.770544;0.637387;0.000000;,
  -0.878472;0.477793;0.000000;,
  0.877736;0.405380;0.255434;,
  0.746645;0.629913;0.213847;,
  0.954223;0.000000;0.299096;,
  0.365138;-0.926994;0.085770;,
  -0.090311;-0.995914;0.000000;,
  -0.096199;-0.995362;0.000000;,
  0.148582;-0.988900;-0.000000;,
  -0.304261;-0.949904;0.071470;,
  -0.986164;0.000000;0.165770;,
  -0.811156;0.544725;0.212838;,
  -0.800406;0.542614;0.254795;,
  -0.351538;-0.931015;-0.098140;,
  0.111436;-0.993772;-0.000000;,
  -0.005626;-0.999984;0.000000;,
  0.292622;-0.952732;-0.081694;,
  0.978448;0.000000;-0.206494;,
  0.798035;0.539043;-0.269394;,
  0.778715;0.539164;-0.320787;,
  0.978055;0.000000;-0.208348;,
  -0.949288;0.000000;-0.314408;,
  -0.857552;0.401219;-0.321913;,
  -0.732183;0.625073;-0.270539;,
  -0.927794;0.000000;-0.373094;,
  -0.693014;-0.173616;0.699707;,
  -0.123686;-0.015158;0.992206;,
  0.119703;-0.021132;0.992585;,
  0.583988;-0.176392;0.792366;,
  0.939170;-0.237293;0.248296;,
  0.971084;-0.238739;-0.000000;,
  0.952264;-0.183017;-0.244333;,
  0.636027;-0.160429;-0.754806;,
  0.157976;-0.021112;-0.987217;,
  -0.093647;-0.015159;-0.995490;,
  -0.527619;-0.160272;-0.834225;,
  -0.920662;-0.236338;-0.310686;,
  -0.971084;-0.238739;0.000000;,
  -0.963009;-0.185990;0.194992;,
  0.599522;0.153396;-0.785521;,
  0.916584;0.146437;-0.372061;,
  0.981438;0.191778;0.000000;,
  0.968110;0.189680;0.163661;,
  0.703535;0.139138;0.696907;,
  0.165239;0.016585;0.986114;,
  -0.099286;0.011744;0.994990;,
  -0.583153;0.139687;0.800263;,
  -0.942913;0.149021;0.297840;,
  -0.981441;0.191766;0.000000;,
  -0.960563;0.188406;-0.204502;,
  -0.635985;0.126269;-0.761301;,
  -0.113162;0.010273;-0.993523;,
  0.165240;0.016585;-0.986114;,
  -0.105066;0.000000;-0.994465;,
  0.115077;0.000000;-0.993357;,
  0.488412;0.000000;-0.872613;,
  0.910736;0.000000;-0.412989;,
  0.976882;0.000000;0.213779;,
  0.672104;0.000000;0.740457;,
  0.153322;0.000000;0.988176;,
  -0.090046;0.000000;0.995938;,
  -0.520517;0.000000;0.853851;,
  -0.943441;0.000000;0.331540;,
  -0.963759;0.000000;-0.266775;,
  -0.570332;-0.274452;0.774208;,
  -0.124595;-0.020073;0.992005;,
  0.136604;-0.025736;0.990291;,
  0.579283;-0.278955;0.765908;,
  0.863178;-0.451727;0.225536;,
  0.886006;-0.463674;-0.000000;,
  0.849373;-0.444498;-0.284582;,
  0.536494;-0.257160;-0.803768;,
  0.136604;-0.025736;-0.990291;,
  -0.124596;-0.020073;-0.992005;,
  -0.527105;-0.252444;-0.811439;,
  -0.849380;-0.444492;-0.284569;,
  -0.885995;-0.463695;0.000000;,
  -0.863159;-0.451770;0.225524;,
  -0.361914;-0.569242;0.738229;,
  -0.112918;-0.474095;0.873203;,
  -0.051463;-0.509449;0.858960;,
  0.098220;-0.380665;0.919482;,
  0.371863;-0.571889;0.731205;,
  0.706923;-0.654257;0.268715;,
  0.749153;-0.662397;-0.000000;,
  0.719172;-0.634312;-0.283620;,
  0.349425;-0.559470;-0.751596;,
  0.098221;-0.380665;-0.919482;,
  0.049640;-0.511579;-0.857801;,
  -0.112918;-0.474095;-0.873203;,
  -0.339391;-0.556588;-0.758303;,
  -0.679100;-0.655627;-0.330118;,
  -0.749198;-0.662346;0.000000;,
  -0.740359;-0.631416;0.230612;,
  -0.119419;-0.019329;0.992656;,
  -0.564512;-0.272243;0.779237;,
  -0.863148;-0.451793;0.225519;,
  -0.885961;-0.463759;0.000000;,
  -0.849328;-0.444597;-0.284563;,
  -0.521033;-0.250092;-0.816075;,
  -0.119420;-0.019329;-0.992656;,
  0.130888;-0.024778;-0.991088;,
  0.529859;-0.254537;-0.808987;,
  0.849371;-0.444506;-0.284577;,
  0.886010;-0.463667;-0.000000;,
  0.863178;-0.451730;0.225532;,
  0.572934;-0.276490;0.771557;,
  0.130887;-0.024778;0.991088;,
  0.967690;0.000000;0.252144;,
  -0.985879;0.000000;0.167457;,
  0.872847;0.000000;0.487994;,
  -0.776439;0.456868;0.434067;,
  -0.872860;0.000000;0.487972;,
  -0.493338;0.788599;-0.367055;,
  0.251625;-0.942838;0.218496;,
  -0.261349;-0.936837;-0.232451;;
  384;
  3;23,24,24;,
  3;24,24,30;,
  3;41,41,41;,
  3;41,41,41;,
  3;21,22,25;,
  3;25,22,31;,
  3;46,47,46;,
  3;46,47,65;,
  3;43,44,69;,
  3;69,44,68;,
  3;72,73,51;,
  3;51,73,50;,
  3;109,2,77;,
  3;77,2,2;,
  3;106,42,81;,
  3;81,42,80;,
  3;83,20,104;,
  3;104,20,20;,
  3;40,113,87;,
  3;87,113,86;,
  3;22,20,31;,
  3;31,20,20;,
  3;42,43,70;,
  3;70,43,69;,
  3;2,23,2;,
  3;2,23,24;,
  3;71,72,40;,
  3;40,72,51;,
  3;20,20,26;,
  3;26,20,102;,
  3;90,91,67;,
  3;67,91,42;,
  3;94,2,29;,
  3;29,2,2;,
  3;98,99,40;,
  3;40,99,74;,
  3;63,64,49;,
  3;49,64,48;,
  3;14,103,85;,
  3;85,103,84;,
  3;100,101,14;,
  3;14,101,33;,
  3;11,39,10;,
  3;10,39,32;,
  3;3,20,11;,
  3;11,20,39;,
  3;41,41,41;,
  3;41,41,41;,
  3;2,38,2;,
  3;2,38,2;,
  3;37,38,7;,
  3;7,38,2;,
  3;17,36,96;,
  3;96,36,95;,
  3;75,76,111;,
  3;111,76,110;,
  3;26,102,15;,
  3;15,102,89;,
  3;82,83,105;,
  3;105,83,104;,
  3;45,46,66;,
  3;66,46,46;,
  3;108,109,78;,
  3;78,109,77;,
  3;93,94,16;,
  3;16,94,29;,
  3;8,13,30;,
  3;24,30,13;,
  3;2,24,2;,
  3;2,24,13;,
  3;41,41,41;,
  3;41,41,41;,
  3;31,20,12;,
  3;12,20,4;,
  3;9,25,12;,
  3;25,31,12;,
  3;33,101,20;,
  3;20,101,20;,
  3;20,84,20;,
  3;20,84,103;,
  3;47,48,65;,
  3;65,48,64;,
  3;2,110,2;,
  3;2,110,76;,
  3;2,95,2;,
  3;2,95,36;,
  3;38,37,23;,
  3;23,37,24;,
  3;2,38,2;,
  3;2,38,23;,
  3;41,41,41;,
  3;41,41,41;,
  3;39,20,22;,
  3;22,20,20;,
  3;32,39,21;,
  3;21,39,22;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;158,52,42;,
  3;42,52,43;,
  3;52,53,43;,
  3;43,53,44;,
  3;91,92,42;,
  3;42,92,54;,
  3;42,107,80;,
  3;80,107,79;,
  3;55,56,45;,
  3;45,56,46;,
  3;56,57,46;,
  3;46,57,47;,
  3;57,58,47;,
  3;47,58,48;,
  3;49,48,59;,
  3;59,48,58;,
  3;112,40,88;,
  3;88,40,87;,
  3;97,98,60;,
  3;60,98,40;,
  3;51,50,62;,
  3;62,50,61;,
  3;40,51,159;,
  3;159,51,62;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;13,52,160;,
  3;160,52,158;,
  3;53,52,8;,
  3;8,52,13;,
  3;16,54,93;,
  3;93,54,92;,
  3;78,79,108;,
  3;108,79,107;,
  3;28,56,1;,
  3;1,56,55;,
  3;18,57,28;,
  3;28,57,56;,
  3;35,58,18;,
  3;18,58,57;,
  3;59,58,0;,
  3;0,58,35;,
  3;111,112,75;,
  3;75,112,88;,
  3;96,97,17;,
  3;17,97,60;,
  3;61,7,62;,
  3;62,7,161;,
  3;159,62,162;,
  3;162,62,161;,
  3;34,64,5;,
  3;5,64,63;,
  3;65,64,19;,
  3;19,64,34;,
  3;46,65,27;,
  3;27,65,19;,
  3;66,46,6;,
  3;6,46,27;,
  3;105,106,82;,
  3;82,106,81;,
  3;89,90,15;,
  3;15,90,67;,
  3;68,9,69;,
  3;69,9,12;,
  3;70,69,4;,
  3;4,69,12;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;11,72,3;,
  3;3,72,71;,
  3;73,72,10;,
  3;10,72,163;,
  3;14,74,100;,
  3;100,74,99;,
  3;85,86,14;,
  3;14,86,113;,
  3;115,144,114;,
  3;114,144,145;,
  3;2,144,2;,
  3;2,144,115;,
  3;157,2,116;,
  3;116,2,2;,
  3;156,157,117;,
  3;117,157,116;,
  3;117,118,156;,
  3;156,118,155;,
  3;154,155,119;,
  3;119,155,118;,
  3;153,154,120;,
  3;120,154,119;,
  3;153,120,152;,
  3;152,120,121;,
  3;122,151,121;,
  3;121,151,152;,
  3;20,20,122;,
  3;122,20,151;,
  3;123,150,20;,
  3;20,150,20;,
  3;149,150,124;,
  3;124,150,123;,
  3;124,125,149;,
  3;149,125,148;,
  3;147,148,126;,
  3;126,148,125;,
  3;146,147,127;,
  3;127,147,126;,
  3;146,127,145;,
  3;145,127,114;,
  3;90,89,68;,
  3;68,89,9;,
  3;44,91,68;,
  3;68,91,90;,
  3;53,92,44;,
  3;44,92,91;,
  3;92,53,93;,
  3;93,53,8;,
  3;30,94,8;,
  3;8,94,93;,
  3;24,2,30;,
  3;30,2,94;,
  3;37,95,24;,
  3;24,95,2;,
  3;96,95,7;,
  3;7,95,37;,
  3;97,96,61;,
  3;61,96,7;,
  3;50,98,61;,
  3;61,98,97;,
  3;73,99,50;,
  3;50,99,98;,
  3;99,73,100;,
  3;100,73,10;,
  3;32,101,10;,
  3;10,101,100;,
  3;20,101,21;,
  3;21,101,32;,
  3;102,20,25;,
  3;25,20,21;,
  3;89,102,9;,
  3;9,102,25;,
  3;14,33,14;,
  3;14,33,103;,
  3;20,103,20;,
  3;20,103,33;,
  3;104,20,26;,
  3;26,20,20;,
  3;105,104,15;,
  3;15,104,26;,
  3;67,106,15;,
  3;15,106,105;,
  3;42,42,67;,
  3;67,42,106;,
  3;54,107,42;,
  3;42,107,42;,
  3;108,107,16;,
  3;16,107,54;,
  3;29,109,16;,
  3;16,109,108;,
  3;2,2,29;,
  3;29,2,109;,
  3;36,110,2;,
  3;2,110,2;,
  3;111,110,17;,
  3;17,110,36;,
  3;60,112,17;,
  3;17,112,111;,
  3;40,40,60;,
  3;60,40,112;,
  3;74,113,40;,
  3;40,113,40;,
  3;14,113,14;,
  3;14,113,74;,
  3;129,115,128;,
  3;128,115,114;,
  3;2,115,130;,
  3;130,115,129;,
  3;116,2,131;,
  3;131,2,130;,
  3;117,116,132;,
  3;132,116,131;,
  3;132,133,117;,
  3;117,133,118;,
  3;119,118,134;,
  3;134,118,133;,
  3;120,119,135;,
  3;135,119,134;,
  3;120,135,121;,
  3;121,135,136;,
  3;137,122,136;,
  3;136,122,121;,
  3;138,20,137;,
  3;137,20,122;,
  3;139,123,138;,
  3;138,123,20;,
  3;124,123,140;,
  3;140,123,139;,
  3;140,141,124;,
  3;124,141,125;,
  3;126,125,142;,
  3;142,125,141;,
  3;127,126,143;,
  3;143,126,142;,
  3;127,143,114;,
  3;114,143,128;,
  3;0,35,128;,
  3;128,35,129;,
  3;129,35,130;,
  3;164,35,18;,
  3;131,130,28;,
  3;28,130,18;,
  3;131,28,132;,
  3;132,28,1;,
  3;55,133,1;,
  3;1,133,132;,
  3;133,55,134;,
  3;134,55,45;,
  3;135,134,66;,
  3;66,134,45;,
  3;136,135,6;,
  3;6,135,66;,
  3;137,136,27;,
  3;27,136,6;,
  3;19,165,27;,
  3;27,138,137;,
  3;139,138,34;,
  3;34,138,19;,
  3;139,34,140;,
  3;140,34,5;,
  3;63,141,5;,
  3;5,141,140;,
  3;141,63,142;,
  3;142,63,49;,
  3;143,142,59;,
  3;59,142,49;,
  3;128,143,0;,
  3;0,143,59;,
  3;2,76,2;,
  3;2,76,144;,
  3;144,76,145;,
  3;145,76,75;,
  3;88,146,75;,
  3;75,146,145;,
  3;88,87,146;,
  3;146,87,147;,
  3;87,86,147;,
  3;147,86,148;,
  3;149,148,85;,
  3;85,148,86;,
  3;85,84,149;,
  3;149,84,150;,
  3;150,84,20;,
  3;20,84,20;,
  3;20,20,151;,
  3;151,20,83;,
  3;151,83,152;,
  3;152,83,82;,
  3;81,153,82;,
  3;82,153,152;,
  3;81,80,153;,
  3;153,80,154;,
  3;80,79,154;,
  3;154,79,155;,
  3;156,155,78;,
  3;78,155,79;,
  3;78,77,156;,
  3;156,77,157;,
  3;77,2,157;,
  3;157,2,2;;
 }
 MeshTextureCoords {
  233;
  0.503240;0.186960;,
  0.503240;0.127990;,
  0.566180;0.186960;,
  0.566180;0.127990;,
  0.566180;0.444600;,
  0.503240;0.444600;,
  0.566180;0.387220;,
  0.503240;0.387220;,
  0.503240;0.622010;,
  0.503240;0.563040;,
  0.566180;0.622010;,
  0.566180;0.563040;,
  0.566180;0.862780;,
  0.503240;0.862780;,
  0.566180;0.805400;,
  0.503240;0.805400;,
  0.762220;0.186960;,
  0.762220;0.127990;,
  0.819600;0.186960;,
  0.819600;0.127990;,
  0.180400;0.186960;,
  0.180400;0.127990;,
  0.237780;0.186960;,
  0.237780;0.127990;,
  0.566180;0.045640;,
  0.503240;0.045640;,
  0.566180;0.025770;,
  0.503240;0.025770;,
  0.819600;0.045640;,
  0.762220;0.045640;,
  0.819600;0.025770;,
  0.762220;0.025770;,
  0.566180;0.724230;,
  0.503240;0.724230;,
  0.566180;0.704360;,
  0.503240;0.704360;,
  0.237780;0.045640;,
  0.180400;0.045640;,
  0.237780;0.025770;,
  0.180400;0.025770;,
  0.503240;0.500000;,
  0.566180;0.500000;,
  0.762220;0.250000;,
  0.819600;0.250000;,
  0.503240;0.250000;,
  0.566180;0.250000;,
  0.180400;0.250000;,
  0.237780;0.250000;,
  0.503240;0.683870;,
  0.503240;0.655200;,
  0.566180;0.683870;,
  0.566180;0.655200;,
  0.819600;0.094800;,
  0.762220;0.094800;,
  0.819600;0.066130;,
  0.762220;0.066130;,
  0.566180;0.094800;,
  0.503240;0.094800;,
  0.566180;0.066130;,
  0.503240;0.066130;,
  0.237780;0.094800;,
  0.180400;0.094800;,
  0.237780;0.066130;,
  0.180400;0.066130;,
  0.375000;0.805400;,
  0.436960;0.805400;,
  0.375000;0.862780;,
  0.436960;0.862780;,
  0.375000;0.704360;,
  0.436960;0.704360;,
  0.375000;0.724230;,
  0.436960;0.724230;,
  0.375000;0.655200;,
  0.436960;0.655200;,
  0.375000;0.683870;,
  0.436960;0.683870;,
  0.375000;0.563040;,
  0.436960;0.563040;,
  0.375000;0.622010;,
  0.436960;0.622010;,
  0.375000;0.500000;,
  0.436960;0.500000;,
  0.375000;0.387220;,
  0.436960;0.387220;,
  0.375000;0.444600;,
  0.436960;0.444600;,
  0.375000;0.186960;,
  0.436960;0.186960;,
  0.375000;0.250000;,
  0.436960;0.250000;,
  0.436960;0.127990;,
  0.375000;0.127990;,
  0.375000;0.066130;,
  0.436960;0.066130;,
  0.375000;0.094800;,
  0.436960;0.094800;,
  0.375000;0.025770;,
  0.436960;0.025770;,
  0.375000;0.045640;,
  0.436960;0.045640;,
  0.625000;0.683870;,
  0.625000;0.655200;,
  0.625000;0.724230;,
  0.625000;0.704360;,
  0.625000;0.862780;,
  0.625000;0.805400;,
  0.625000;0.045640;,
  0.625000;0.025770;,
  0.625000;0.094800;,
  0.625000;0.066130;,
  0.625000;0.127990;,
  0.625000;0.186960;,
  0.625000;0.250000;,
  0.625000;0.444600;,
  0.625000;0.387220;,
  0.625000;0.563040;,
  0.625000;0.500000;,
  0.625000;0.622010;,
  0.375000;0.323730;,
  0.436960;0.323730;,
  0.503240;0.323730;,
  0.566180;0.323730;,
  0.625000;0.323730;,
  0.698730;0.250000;,
  0.698730;0.186960;,
  0.698730;0.127990;,
  0.698730;0.094800;,
  0.698730;0.066130;,
  0.698730;0.045640;,
  0.698730;0.025770;,
  0.625000;0.926270;,
  0.566180;0.926270;,
  0.503240;0.926270;,
  0.436960;0.926270;,
  0.375000;0.926270;,
  0.301270;0.045640;,
  0.301270;0.025770;,
  0.301270;0.094800;,
  0.301270;0.066130;,
  0.301270;0.186960;,
  0.301270;0.127990;,
  0.301270;0.250000;,
  0.566180;1.000000;,
  0.625000;1.000000;,
  0.503240;1.000000;,
  0.436960;1.000000;,
  0.375000;1.000000;,
  0.436960;0.750000;,
  0.375000;0.750000;,
  0.503240;0.750000;,
  0.566180;0.750000;,
  0.625000;0.750000;,
  0.875000;0.045640;,
  0.875000;0.025770;,
  0.875000;0.094800;,
  0.875000;0.066130;,
  0.875000;0.127990;,
  0.875000;0.186960;,
  0.875000;0.250000;,
  0.125000;0.186960;,
  0.125000;0.250000;,
  0.125000;0.127990;,
  0.125000;0.066130;,
  0.125000;0.094800;,
  0.125000;0.025770;,
  0.125000;0.045640;,
  0.436960;0.010240;,
  0.436960;0.013840;,
  0.375000;0.010240;,
  0.375000;0.013840;,
  0.503240;0.013840;,
  0.503240;0.010240;,
  0.566180;0.013840;,
  0.566180;0.010240;,
  0.625000;0.013840;,
  0.625000;0.010240;,
  0.698730;0.010240;,
  0.698730;0.013840;,
  0.762220;0.013840;,
  0.762220;0.010240;,
  0.819600;0.013840;,
  0.819600;0.010240;,
  0.875000;0.013840;,
  0.875000;0.010240;,
  0.566180;0.739760;,
  0.566180;0.736160;,
  0.625000;0.739760;,
  0.625000;0.736160;,
  0.503240;0.739760;,
  0.503240;0.736160;,
  0.436960;0.739760;,
  0.436960;0.736160;,
  0.375000;0.736160;,
  0.375000;0.739760;,
  0.125000;0.010240;,
  0.180400;0.010240;,
  0.125000;0.013840;,
  0.180400;0.013840;,
  0.237780;0.013840;,
  0.237780;0.010240;,
  0.301270;0.013840;,
  0.301270;0.010240;,
  0.436960;0.005570;,
  0.375000;0.005570;,
  0.503240;0.005570;,
  0.566180;0.005570;,
  0.625000;0.005570;,
  0.698730;0.005570;,
  0.762220;0.005570;,
  0.819600;0.005570;,
  0.875000;0.005570;,
  0.566180;0.744430;,
  0.625000;0.744430;,
  0.503240;0.744430;,
  0.436960;0.744430;,
  0.375000;0.744430;,
  0.125000;0.005570;,
  0.180400;0.005570;,
  0.237780;0.005570;,
  0.301270;0.005570;,
  0.375000;0.000000;,
  0.436960;0.000000;,
  0.503240;0.000000;,
  0.566180;0.000000;,
  0.625000;0.000000;,
  0.698730;0.000000;,
  0.762220;0.000000;,
  0.819600;0.000000;,
  0.875000;0.000000;,
  0.180400;0.000000;,
  0.125000;0.000000;,
  0.237780;0.000000;,
  0.301270;0.000000;;
 }
}
