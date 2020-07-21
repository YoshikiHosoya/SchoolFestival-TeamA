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
 260;
 -5.55632;-8.88918;-4.25278;,
 -3.44465;-11.53761;-2.52670;,
 -6.92966;-8.88918;-2.52670;,
 -3.44465;-8.88918;-5.14921;,
 0.04030;-11.53761;0.09575;,
 -3.44465;-11.53761;0.09575;,
 0.04030;-11.53761;-2.52670;,
 -3.44465;-11.53761;3.24275;,
 3.52531;-11.53761;-2.52670;,
 -6.92966;-8.88918;3.24275;,
 -5.65555;-8.88918;4.98990;,
 0.04030;-11.53761;3.24275;,
 3.52531;-11.53761;0.09575;,
 5.63693;-8.88918;-4.25278;,
 3.52531;-8.88918;-5.14921;,
 -5.55632;-1.17612;-4.25278;,
 -6.92966;-1.17612;-2.52670;,
 -6.42622;2.68042;-2.52670;,
 -5.15212;2.68042;-4.25278;,
 -3.44465;-8.88918;5.34071;,
 -3.44465;-1.17612;-5.14921;,
 -5.55632;-1.17612;-4.25278;,
 -5.15212;2.68042;-4.25278;,
 -3.19296;2.68042;-5.14921;,
 3.52531;-11.53761;3.24275;,
 7.01026;-8.88918;-2.52670;,
 -4.31652;6.53695;-3.22177;,
 -5.27574;6.53695;-1.99992;,
 -2.61769;6.53695;-4.09559;,
 -4.31652;6.53695;-3.22177;,
 -6.42622;2.68042;3.24275;,
 -6.92966;-1.17612;3.24275;,
 -5.65555;-1.17612;4.98990;,
 -5.24417;2.68042;4.98990;,
 3.52531;-8.88918;5.34071;,
 5.73615;-8.88918;4.98990;,
 7.01026;-8.88918;3.24275;,
 5.23272;2.68042;-4.25278;,
 5.63693;-1.17612;-4.25278;,
 3.52531;-1.17612;-5.14921;,
 3.27363;2.68042;-5.14921;,
 -3.44465;-1.17612;5.34071;,
 -3.19296;2.68042;5.34071;,
 -5.27574;6.53695;-1.99992;,
 -2.61769;9.17963;-1.99992;,
 -4.28597;6.53695;3.41153;,
 -5.27574;6.53695;2.61058;,
 2.69835;6.53695;-4.09559;,
 4.39712;6.53695;-3.22177;,
 6.50689;2.68042;-2.52670;,
 7.01026;-1.17612;-2.52670;,
 5.63693;-1.17612;-4.25278;,
 5.23272;2.68042;-4.25278;,
 -2.61769;6.53695;4.28715;,
 4.39712;6.53695;-3.22177;,
 5.35634;6.53695;-1.99992;,
 -1.67981;9.17963;-1.78070;,
 -1.67981;10.12851;-1.78070;,
 -1.38099;9.17963;-1.78070;,
 -2.61769;9.17963;2.61058;,
 -5.27574;6.53695;2.61058;,
 -2.25788;9.17963;-0.82708;,
 -2.25788;10.12851;-0.82708;,
 -1.98619;9.17963;-1.27524;,
 2.69835;9.17963;-1.99992;,
 -1.67981;12.10706;-1.78070;,
 -1.04406;10.12851;-1.78070;,
 -2.25788;12.10706;-0.82708;,
 -1.67981;10.12851;-1.78070;,
 -2.25788;9.17963;1.08983;,
 -2.25788;10.12851;0.49768;,
 -2.25788;9.17963;0.49768;,
 0.11196;9.17963;-1.78070;,
 0.11196;10.12851;-1.78070;,
 0.62237;9.17963;-1.78070;,
 -1.67981;12.10706;-1.78070;,
 -1.04406;12.10706;-1.78070;,
 -2.25788;12.10706;0.49768;,
 0.11196;12.10706;-1.78070;,
 1.19803;9.17963;-1.78070;,
 1.19803;10.12851;-1.78070;,
 1.46236;9.17963;-1.78070;,
 5.35634;6.53695;-1.99992;,
 -2.25788;12.10706;-0.82708;,
 -1.04406;12.10706;-0.82708;,
 -2.25788;10.12851;1.75770;,
 3.52531;-1.17612;5.34071;,
 5.73615;-1.17612;4.98990;,
 5.32477;2.68042;4.98990;,
 3.27363;2.68042;5.34071;,
 -1.04406;12.10706;0.49768;,
 -2.25788;12.10706;0.49768;,
 1.19803;12.10706;-1.78070;,
 1.76041;10.12851;-1.78070;,
 7.01026;-1.17612;3.24275;,
 6.50689;2.68042;3.24275;,
 -2.25788;12.10706;1.75770;,
 -1.35412;9.09423;2.66473;,
 -1.67981;10.12851;2.66473;,
 -1.67981;9.09423;2.66473;,
 0.11196;12.10706;-0.82708;,
 2.06685;9.17963;-1.27524;,
 2.33855;10.12851;-0.82708;,
 2.33855;9.17963;-0.82708;,
 2.33855;9.17963;-0.20451;,
 1.76041;12.10706;-1.78070;,
 -0.45189;9.09423;2.66479;,
 -1.04406;10.12851;2.66473;,
 -1.04406;9.09423;2.66473;,
 -1.67981;12.10706;2.66473;,
 0.11196;12.10706;0.49768;,
 -1.04406;12.10706;1.75770;,
 -2.25788;12.10706;1.75770;,
 1.76041;10.12851;-1.78070;,
 2.33855;12.10706;-0.82708;,
 1.19803;12.10706;-0.82708;,
 1.76041;12.10706;-1.78070;,
 1.19803;12.10706;0.49768;,
 2.69835;6.53695;4.28715;,
 4.36663;6.53695;3.41153;,
 2.33855;12.10706;-0.82708;,
 2.33855;10.12851;0.49768;,
 0.11196;12.10706;1.75770;,
 0.11196;10.12851;2.66479;,
 -1.04406;12.10706;2.66473;,
 1.19803;9.09423;2.66479;,
 1.19803;10.12851;2.66479;,
 0.64169;9.09423;2.66479;,
 5.35634;6.53695;2.61058;,
 2.33855;9.17963;1.16555;,
 2.33855;10.12851;1.75770;,
 2.33855;9.17963;1.75770;,
 1.48612;9.09423;2.66479;,
 2.33855;12.10706;0.49768;,
 2.33855;12.10706;0.49768;,
 0.11196;12.10706;2.66479;,
 1.19803;12.10706;1.75770;,
 2.69835;9.17963;2.61058;,
 1.19803;12.10706;2.66479;,
 5.35634;6.53695;2.61058;,
 2.33855;12.10706;1.75770;,
 1.76041;10.12851;2.66473;,
 2.33855;12.10706;1.75770;,
 1.76041;12.10706;2.66473;,
 -6.92966;-8.88918;0.09575;,
 -5.55632;-8.88918;-4.25278;,
 -6.92966;-8.88918;-2.52670;,
 -6.92966;-4.26132;-2.52670;,
 -5.55632;-4.26132;-4.25278;,
 -5.55632;-4.26132;-4.25278;,
 -3.44465;-4.26132;-5.14921;,
 0.04030;-8.88918;-5.14921;,
 -6.92966;-8.88918;0.09575;,
 -6.92966;-4.26132;0.09575;,
 0.04030;-4.26132;-5.14921;,
 -6.92966;-8.88918;3.24275;,
 -6.92966;-4.26132;3.24275;,
 -6.92966;-1.17612;0.09575;,
 3.52531;-4.26132;-5.14921;,
 0.04030;-1.17612;-5.14921;,
 -5.65555;-8.88918;4.98990;,
 -5.65555;-4.26132;4.98990;,
 0.04030;-8.88918;5.34071;,
 -6.42622;2.68042;0.09575;,
 5.63693;-4.26132;-4.25278;,
 7.01026;-8.88918;0.09575;,
 0.04030;2.68042;-5.14921;,
 -3.44465;-8.88918;5.34071;,
 -3.44465;-4.26132;5.34071;,
 7.01026;-4.26132;-2.52670;,
 7.01026;-8.88918;-2.52670;,
 5.63693;-8.88918;-4.25278;,
 5.63693;-4.26132;-4.25278;,
 0.04030;-4.26132;5.34071;,
 0.04030;-8.88918;5.34071;,
 -5.27574;6.53695;0.09575;,
 0.04030;6.53695;-4.09559;,
 7.01026;-4.26132;0.09575;,
 7.01026;-8.88918;0.09575;,
 3.52531;-4.26132;5.34071;,
 3.52531;-8.88918;5.34071;,
 0.04030;-1.17612;5.34071;,
 7.01026;-4.26132;3.24275;,
 7.01026;-8.88918;3.24275;,
 -5.27574;6.53695;0.09575;,
 -2.61769;9.17963;0.09575;,
 7.01026;-1.17612;0.09575;,
 5.73615;-4.26132;4.98990;,
 5.73615;-8.88918;4.98990;,
 0.04030;9.17963;-1.99992;,
 0.04030;2.68042;5.34071;,
 6.50689;2.68042;0.09575;,
 -1.04406;9.17963;-1.78070;,
 -2.25788;9.17963;-0.12489;,
 -0.43130;9.17963;-1.78070;,
 -2.25788;9.17963;0.09575;,
 0.04030;9.17963;-1.78070;,
 0.04030;6.53695;4.28715;,
 -2.25788;9.17963;1.75770;,
 1.76041;9.17963;-1.78070;,
 5.35634;6.53695;0.09575;,
 -2.05416;9.17963;2.07735;,
 -1.71431;9.17963;2.61058;,
 -1.95144;9.17963;2.23851;,
 -1.95144;9.17963;2.23851;,
 -1.71431;9.17963;2.61058;,
 2.69835;9.17963;0.09575;,
 5.35634;6.53695;0.09575;,
 0.11196;9.09423;2.66479;,
 2.33855;9.17963;0.49768;,
 2.13476;9.17963;2.07735;,
 2.03211;9.17963;2.23851;,
 1.79497;9.17963;2.61058;,
 2.03211;9.17963;2.23851;,
 1.76041;9.09423;2.66473;,
 1.79497;9.17963;2.61058;,
 -1.89319;9.17963;-1.42865;,
 -1.67981;9.17963;-1.78070;,
 -2.05416;9.17963;2.07735;,
 1.76041;9.17963;-1.78070;,
 1.97379;9.17963;-1.42865;,
 2.33855;9.17963;0.09575;,
 0.04030;9.09423;2.66479;,
 2.13476;9.17963;2.07735;,
 -2.25788;9.17963;-0.82708;,
 -2.25788;9.17963;0.09575;,
 -2.25788;9.17963;-0.12489;,
 -1.98619;9.17963;-1.27524;,
 -1.89319;9.17963;-1.42865;,
 -2.25788;9.17963;1.75770;,
 -2.25788;9.17963;1.08983;,
 -2.25788;9.17963;0.49768;,
 1.97379;9.17963;-1.42865;,
 2.06685;9.17963;-1.27524;,
 2.33855;9.17963;-0.82708;,
 2.33855;9.17963;-0.20451;,
 2.33855;9.17963;0.09575;,
 2.33855;9.17963;1.75770;,
 2.33855;9.17963;0.49768;,
 2.33855;9.17963;1.16555;,
 -1.67981;9.17963;-1.78070;,
 -1.38099;9.17963;-1.78070;,
 -1.04406;9.17963;-1.78070;,
 -0.43130;9.17963;-1.78070;,
 0.04030;9.17963;-1.78070;,
 0.11196;9.17963;-1.78070;,
 0.62237;9.17963;-1.78070;,
 1.19803;9.17963;-1.78070;,
 1.46236;9.17963;-1.78070;,
 1.76041;9.17963;-1.78070;,
 -1.67981;9.09423;2.66473;,
 -1.35412;9.09423;2.66473;,
 -1.04406;9.09423;2.66473;,
 -0.45189;9.09423;2.66479;,
 0.04030;9.09423;2.66479;,
 0.11196;9.09423;2.66479;,
 0.64169;9.09423;2.66479;,
 1.19803;9.09423;2.66479;,
 1.48612;9.09423;2.66479;,
 1.76041;9.09423;2.66473;;
 
 260;
 3;0,1,2;,
 3;0,3,1;,
 3;4,5,1;,
 3;4,1,6;,
 3;4,7,5;,
 3;8,4,6;,
 3;9,7,10;,
 3;11,7,4;,
 3;12,4,8;,
 3;13,8,14;,
 4;15,16,17,18;,
 3;10,7,19;,
 4;20,21,22,23;,
 3;24,11,4;,
 3;24,4,12;,
 3;25,8,13;,
 4;26,18,17,27;,
 4;28,23,22,29;,
 4;30,31,32,33;,
 3;34,24,35;,
 3;35,24,36;,
 4;37,38,39,40;,
 4;33,32,41,42;,
 3;43,44,29;,
 3;29,44,28;,
 4;30,33,45,46;,
 4;37,40,47,48;,
 4;49,50,51,52;,
 4;33,42,53,45;,
 4;49,52,54,55;,
 3;56,57,58;,
 3;45,59,60;,
 3;61,62,63;,
 3;47,64,48;,
 3;65,66,57;,
 3;67,68,62;,
 3;45,53,59;,
 3;69,70,71;,
 3;72,73,74;,
 3;75,68,67;,
 3;76,66,65;,
 3;77,62,70;,
 3;73,66,78;,
 3;67,62,77;,
 3;79,80,81;,
 3;78,66,76;,
 3;48,64,82;,
 3;83,84,65;,
 3;65,84,76;,
 3;78,80,73;,
 3;70,85,77;,
 3;76,84,78;,
 4;86,87,88,89;,
 3;83,90,84;,
 3;91,90,83;,
 3;92,93,80;,
 4;87,94,95,88;,
 3;92,80,78;,
 3;77,85,96;,
 3;97,98,99;,
 3;78,84,100;,
 3;101,102,103;,
 3;78,100,92;,
 3;103,102,104;,
 3;105,93,92;,
 3;106,107,108;,
 3;109,85,98;,
 3;100,84,110;,
 3;96,85,109;,
 3;110,84,90;,
 3;91,111,90;,
 3;112,111,91;,
 3;102,113,114;,
 3;92,100,115;,
 3;114,113,116;,
 3;92,115,105;,
 3;98,107,109;,
 3;115,100,117;,
 3;109,111,112;,
 3;117,100,110;,
 4;118,89,88,119;,
 3;105,115,120;,
 3;114,121,102;,
 3;110,90,122;,
 3;122,90,111;,
 3;107,123,124;,
 3;109,107,124;,
 3;125,126,127;,
 3;124,111,109;,
 4;119,88,95,128;,
 3;129,130,131;,
 3;132,126,125;,
 3;120,115,133;,
 3;133,115,117;,
 3;134,121,114;,
 3;135,111,124;,
 3;117,110,136;,
 3;124,123,135;,
 3;122,111,135;,
 3;136,110,122;,
 3;119,137,118;,
 3;138,123,126;,
 3;139,137,119;,
 3;130,121,140;,
 3;135,123,138;,
 3;140,121,134;,
 3;126,141,138;,
 3;138,122,135;,
 3;133,117,142;,
 3;136,122,138;,
 3;142,117,136;,
 3;141,130,143;,
 3;143,130,140;,
 3;138,141,143;,
 3;143,136,138;,
 3;142,136,143;,
 4;2,1,5,144;,
 4;145,146,147,148;,
 4;149,150,3,0;,
 4;6,1,3,151;,
 4;147,146,152,153;,
 4;144,5,7,9;,
 4;3,150,154,151;,
 4;148,147,16,15;,
 4;8,6,151,14;,
 4;21,20,150,149;,
 4;153,152,155,156;,
 4;16,147,153,157;,
 4;151,154,158,14;,
 4;154,150,20,159;,
 4;156,155,160,161;,
 4;157,153,156,31;,
 4;19,7,11,162;,
 4;17,16,157,163;,
 4;14,158,164,13;,
 4;165,12,8,25;,
 4;158,154,159,39;,
 4;159,20,23,166;,
 4;160,167,168,161;,
 4;31,156,161,32;,
 4;163,157,31,30;,
 4;162,11,24,34;,
 4;169,170,171,172;,
 4;36,24,12,165;,
 4;164,158,39,38;,
 4;173,168,167,174;,
 4;39,159,166,40;,
 4;27,17,163,175;,
 4;161,168,41,32;,
 4;166,23,28,176;,
 4;177,178,170,169;,
 4;50,169,172,51;,
 4;175,163,30,46;,
 4;179,173,174,180;,
 4;181,41,168,173;,
 4;40,166,176,47;,
 4;182,183,178,177;,
 4;184,185,44,43;,
 4;186,177,169,50;,
 4;187,179,180,188;,
 4;28,44,189,176;,
 4;188,183,182,187;,
 4;86,181,173,179;,
 4;190,42,41,181;,
 4;60,59,185,184;,
 4;94,182,177,186;,
 4;176,189,64,47;,
 4;191,186,50,49;,
 4;58,57,66,192;,
 4;193,70,62,61;,
 4;87,86,179,187;,
 4;192,66,73,194;,
 4;70,193,195,71;,
 4;194,73,72,196;,
 4;187,182,94,87;,
 4;89,190,181,86;,
 4;53,42,190,197;,
 4;74,73,80,79;,
 4;198,85,70,69;,
 4;95,94,186,191;,
 4;81,80,93,199;,
 4;200,191,49,55;,
 4;201,59,202,203;,
 4;98,204,205,99;,
 4;82,64,206,207;,
 4;197,190,89,118;,
 4;108,107,98,97;,
 4;128,95,191,200;,
 4;127,126,123,208;,
 4;209,121,130,129;,
 4;207,206,137,139;,
 4;137,210,211,212;,
 4;213,141,214,215;,
 4;214,141,126,132;,
 3;62,68,63;,
 3;63,68,216;,
 3;68,217,216;,
 3;98,85,204;,
 3;204,85,218;,
 3;85,198,218;,
 3;219,113,220;,
 3;113,102,220;,
 3;102,101,220;,
 3;102,121,104;,
 3;104,121,221;,
 3;121,209,221;,
 3;208,123,222;,
 3;222,123,106;,
 3;123,107,106;,
 3;131,130,223;,
 3;223,130,213;,
 3;130,141,213;,
 3;44,185,224;,
 3;185,225,226;,
 3;226,224,185;,
 3;44,224,227;,
 3;227,228,44;,
 3;185,59,225;,
 3;59,201,229;,
 3;59,229,230;,
 3;59,230,225;,
 3;230,231,225;,
 3;232,233,64;,
 3;233,234,64;,
 3;234,235,64;,
 3;235,236,64;,
 3;236,206,64;,
 3;210,137,237;,
 3;236,238,206;,
 3;238,239,206;,
 3;239,237,206;,
 3;237,137,206;,
 3;44,228,240;,
 3;44,240,189;,
 3;240,241,189;,
 3;241,242,189;,
 3;242,243,189;,
 3;243,244,189;,
 3;189,244,64;,
 3;244,245,64;,
 3;245,246,64;,
 3;246,247,64;,
 3;247,248,64;,
 3;248,249,64;,
 3;249,232,64;,
 3;59,53,202;,
 3;53,197,250;,
 3;250,197,251;,
 3;251,197,252;,
 3;252,197,253;,
 3;197,254,253;,
 3;250,202,53;,
 3;197,118,254;,
 3;254,118,255;,
 3;255,118,256;,
 3;256,118,257;,
 3;257,118,258;,
 3;258,118,259;,
 3;259,118,212;,
 3;118,137,212;;
 
 MeshMaterialList {
  2;
  260;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.693600;0.508000;0.360800;1.000000;;
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
 }
 MeshNormals {
  145;
  -0.556188;-0.385436;-0.736270;,
  -0.265757;-0.903230;-0.336971;,
  -0.846337;-0.436785;-0.304849;,
  -0.186170;-0.377313;-0.907180;,
  0.000000;-1.000000;-0.000000;,
  -0.319232;-0.947677;0.000000;,
  0.000000;-0.922936;-0.384954;,
  -0.241507;-0.896994;0.370237;,
  0.265761;-0.903228;-0.336972;,
  -0.852450;-0.438094;0.285312;,
  -0.471717;-0.386358;0.792598;,
  0.000000;-0.900260;0.435353;,
  0.319236;-0.947675;-0.000000;,
  0.556193;-0.385433;-0.736268;,
  0.186175;-0.377313;-0.907179;,
  -0.943797;0.058859;-0.325243;,
  -0.924911;0.216422;-0.312571;,
  -0.611068;0.032759;-0.790900;,
  -0.074324;-0.328218;0.941674;,
  -0.613594;0.192867;-0.765706;,
  -0.202731;0.008691;-0.979196;,
  0.241510;-0.896993;0.370238;,
  0.846339;-0.436780;-0.304850;,
  -0.211570;0.156095;-0.964817;,
  -0.559351;0.468976;-0.683512;,
  -0.204952;0.458854;-0.864551;,
  -0.810051;0.513642;-0.282822;,
  -0.950365;0.059408;0.305413;,
  -0.526246;0.029900;0.849807;,
  -0.918589;0.230320;0.321164;,
  0.074326;-0.328218;0.941673;,
  0.471720;-0.386355;0.792597;,
  0.852452;-0.438090;0.285312;,
  -0.525470;0.219160;0.822101;,
  0.611071;0.032757;-0.790898;,
  0.202737;0.008691;-0.979195;,
  0.613594;0.192866;-0.765706;,
  0.211576;0.156095;-0.964816;,
  -0.080096;0.003476;0.996781;,
  -0.212776;0.944506;-0.250271;,
  -0.490836;0.441877;0.750883;,
  -0.118846;0.161893;0.979626;,
  0.204958;0.458854;-0.864549;,
  -0.783795;0.512168;0.351211;,
  0.943796;0.058852;-0.325246;,
  0.924909;0.216422;-0.312577;,
  -0.120547;0.462910;0.878170;,
  0.559355;0.468973;-0.683510;,
  -0.490754;0.000000;-0.871298;,
  -0.607421;-0.000009;-0.794380;,
  0.000000;0.000000;-1.000000;,
  -0.210723;0.932988;0.291769;,
  -0.963102;0.000000;-0.269138;,
  -0.963106;-0.000004;-0.269124;,
  -0.855142;-0.000020;-0.518394;,
  0.114879;0.984147;-0.135120;,
  -0.321533;0.000000;-0.946898;,
  -0.933999;0.000000;-0.357276;,
  -1.000000;0.000000;0.000000;,
  0.810050;0.513643;-0.282825;,
  0.000000;1.000000;0.000000;,
  -0.937133;0.000001;0.348972;,
  0.525470;0.219158;0.822101;,
  0.080099;0.003476;0.996781;,
  0.526245;0.029898;0.849807;,
  0.559012;-0.000008;-0.829160;,
  0.950364;0.059401;0.305416;,
  0.918589;0.230318;0.321167;,
  -0.960025;0.000000;0.279914;,
  0.000000;0.278927;0.960312;,
  -0.480928;-0.000003;0.876760;,
  -0.189150;0.360582;0.913347;,
  0.855057;0.000073;-0.518534;,
  0.951586;0.000014;-0.307382;,
  0.963101;0.000000;-0.269142;,
  0.118848;0.161892;0.979625;,
  1.000000;0.000000;0.000000;,
  0.490703;0.000000;-0.871327;,
  -0.000052;0.222762;0.974873;,
  -0.000036;0.000005;1.000000;,
  -0.000051;0.278919;0.960315;,
  -0.480911;0.000000;0.876770;,
  0.963101;0.000000;-0.269142;,
  0.065280;0.497698;0.864891;,
  -0.000020;0.000004;1.000000;,
  -0.000036;0.000000;1.000000;,
  0.000000;0.278919;0.960315;,
  0.000047;0.000003;1.000000;,
  0.490842;0.441880;0.750877;,
  0.937132;-0.000018;0.348975;,
  0.960004;0.000000;0.279986;,
  0.000095;0.278941;0.960308;,
  0.783797;0.512170;0.351203;,
  0.275064;0.882777;0.380846;,
  0.000056;0.000000;1.000000;,
  0.982597;0.000000;0.185751;,
  0.480909;0.000010;0.876770;,
  0.630754;0.000000;0.775982;,
  -0.895840;-0.444377;0.000000;,
  -0.944068;0.000000;-0.329750;,
  -0.605256;0.000000;-0.796031;,
  -0.199383;0.000000;-0.979922;,
  0.000000;-0.380410;-0.924818;,
  -0.950782;0.000000;0.309860;,
  -0.997894;0.064858;0.000000;,
  0.199388;0.000000;-0.979921;,
  -0.521864;0.000000;0.853029;,
  0.000000;-0.328739;0.944421;,
  -0.978060;0.208325;0.000000;,
  0.605261;0.000000;-0.796027;,
  0.895842;-0.444373;-0.000000;,
  0.000000;0.132953;-0.991122;,
  -0.078600;0.000000;0.996906;,
  0.944068;0.000000;-0.329750;,
  0.000000;0.000000;1.000000;,
  -0.858168;0.513370;0.000000;,
  0.000000;0.451620;-0.892211;,
  0.078603;0.000000;0.996906;,
  0.950782;0.000000;0.309860;,
  -0.251859;0.967764;0.000000;,
  0.997895;0.064850;0.000000;,
  0.521866;0.000000;0.853028;,
  0.000000;0.977384;-0.211472;,
  0.000000;0.132946;0.991123;,
  0.978060;0.208324;0.000000;,
  -0.000011;0.471592;0.881817;,
  -0.960025;0.000000;0.279914;,
  0.490754;0.000000;-0.871298;,
  0.858166;0.513372;0.000000;,
  0.000133;0.775031;0.631923;,
  0.214586;0.976705;0.000000;,
  0.000000;0.278919;0.960315;,
  -0.000133;0.775031;0.631923;,
  0.240709;0.305879;0.921139;,
  -0.855165;-0.000017;-0.518356;,
  0.855100;0.000032;-0.518463;,
  0.000000;0.334139;0.942524;,
  -0.000027;0.000000;1.000000;,
  -0.843310;-0.000000;0.537427;,
  -0.843360;-0.000010;0.537349;,
  0.843276;-0.000039;0.537481;,
  0.843135;0.000019;0.537702;,
  -0.843285;0.000008;0.537467;,
  0.843320;-0.000078;0.537412;,
  0.000000;0.000000;0.000000;;
  260;
  3;0,1,2;,
  3;0,3,1;,
  3;4,5,1;,
  3;4,1,6;,
  3;4,7,5;,
  3;8,4,6;,
  3;9,7,10;,
  3;11,7,4;,
  3;12,4,8;,
  3;13,8,14;,
  4;17,15,16,19;,
  3;10,7,18;,
  4;20,17,19,23;,
  3;21,11,4;,
  3;21,4,12;,
  3;22,8,13;,
  4;24,19,16,26;,
  4;25,23,19,24;,
  4;29,27,28,33;,
  3;30,21,31;,
  3;31,21,32;,
  4;36,34,35,37;,
  4;33,28,38,41;,
  3;26,39,24;,
  3;24,39,25;,
  4;29,33,40,43;,
  4;36,37,42,47;,
  4;45,44,34,36;,
  4;33,41,46,40;,
  4;45,36,47,59;,
  3;48,49,50;,
  3;40,51,43;,
  3;52,53,54;,
  3;42,55,47;,
  3;56,50,49;,
  3;57,49,53;,
  3;40,46,51;,
  3;58,58,58;,
  3;50,50,50;,
  3;56,49,57;,
  3;50,50,56;,
  3;58,53,58;,
  3;50,50,50;,
  3;57,53,58;,
  3;50,50,50;,
  3;50,50,50;,
  3;47,55,59;,
  3;60,60,60;,
  3;60,60,60;,
  3;50,50,50;,
  3;58,61,58;,
  3;60,60,60;,
  4;63,64,62,75;,
  3;60,60,60;,
  3;60,60,60;,
  3;50,65,50;,
  4;64,66,67,62;,
  3;50,50,50;,
  3;58,61,68;,
  3;69,70,71;,
  3;60,60,60;,
  3;72,73,74;,
  3;60,60,60;,
  3;74,73,76;,
  3;77,65,50;,
  3;78,79,80;,
  3;81,61,70;,
  3;60,60,60;,
  3;68,61,81;,
  3;60,60,60;,
  3;60,60,60;,
  3;60,60,60;,
  3;73,65,82;,
  3;60,60,60;,
  3;82,65,77;,
  3;60,60,60;,
  3;70,79,81;,
  3;60,60,60;,
  3;60,60,60;,
  3;60,60,60;,
  4;83,75,62,88;,
  3;60,60,60;,
  3;82,76,73;,
  3;60,60,60;,
  3;60,60,60;,
  3;79,84,85;,
  3;81,79,85;,
  3;86,87,86;,
  3;60,60,60;,
  4;88,62,67,92;,
  3;76,89,90;,
  3;91,87,86;,
  3;60,60,60;,
  3;60,60,60;,
  3;76,76,82;,
  3;60,60,60;,
  3;60,60,60;,
  3;85,84,137;,
  3;60,60,60;,
  3;60,60,60;,
  3;88,93,83;,
  3;94,84,87;,
  3;92,93,88;,
  3;89,76,95;,
  3;137,84,94;,
  3;95,76,76;,
  3;87,96,94;,
  3;60,60,60;,
  3;60,60,60;,
  3;60,60,60;,
  3;60,60,60;,
  3;96,89,97;,
  3;97,89,95;,
  3;94,96,97;,
  3;60,60,60;,
  3;60,60,60;,
  4;2,1,5,98;,
  4;0,2,99,100;,
  4;100,101,3,0;,
  4;6,1,3,102;,
  4;99,2,98,58;,
  4;98,5,7,9;,
  4;3,101,50,102;,
  4;100,99,15,17;,
  4;8,6,102,14;,
  4;17,20,101,100;,
  4;58,98,9,103;,
  4;15,99,58,104;,
  4;102,50,105,14;,
  4;50,101,20,50;,
  4;103,9,10,106;,
  4;104,58,103,27;,
  4;18,7,11,107;,
  4;16,15,104,108;,
  4;14,105,109,13;,
  4;110,12,8,22;,
  4;105,50,50,35;,
  4;50,20,23,111;,
  4;10,18,112,106;,
  4;27,103,106,28;,
  4;108,104,27,29;,
  4;107,11,21,30;,
  4;113,22,13,109;,
  4;32,21,12,110;,
  4;109,105,35,34;,
  4;114,112,18,107;,
  4;35,50,111,37;,
  4;26,16,108,115;,
  4;106,112,38,28;,
  4;111,23,25,116;,
  4;76,110,22,113;,
  4;44,113,109,34;,
  4;115,108,29,43;,
  4;117,114,107,30;,
  4;114,38,112,114;,
  4;37,111,116,42;,
  4;118,32,110,76;,
  4;115,119,39,26;,
  4;120,76,113,44;,
  4;121,117,30,31;,
  4;25,39,122,116;,
  4;31,32,118,121;,
  4;63,114,114,117;,
  4;123,41,38,114;,
  4;43,51,119,115;,
  4;66,118,76,120;,
  4;116,122,55,42;,
  4;124,120,44,45;,
  4;50,49,50,50;,
  4;58,58,53,52;,
  4;64,63,117,121;,
  4;50,50,50,50;,
  4;58,58,58,58;,
  4;50,50,50,50;,
  4;121,118,66,64;,
  4;75,123,114,63;,
  4;46,41,123,125;,
  4;50,50,50,50;,
  4;126,61,58,58;,
  4;67,66,120,124;,
  4;50,50,65,127;,
  4;128,124,45,59;,
  4;60,51,129,60;,
  4;70,138,139,71;,
  4;59,55,130,128;,
  4;125,123,75,83;,
  4;80,79,70,69;,
  4;92,67,124,128;,
  4;86,87,84,131;,
  4;76,76,89,76;,
  4;128,130,93,92;,
  4;93,60,60,132;,
  4;140,96,133,141;,
  4;133,96,87,91;,
  3;53,49,54;,
  3;54,49,134;,
  3;49,48,134;,
  3;70,61,138;,
  3;138,61,142;,
  3;61,126,142;,
  3;127,65,135;,
  3;65,73,135;,
  3;73,72,135;,
  3;73,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;131,84,136;,
  3;136,84,78;,
  3;84,79,78;,
  3;90,89,143;,
  3;143,89,140;,
  3;89,96,140;,
  3;39,119,60;,
  3;119,60,60;,
  3;60,60,119;,
  3;39,60,60;,
  3;60,60,39;,
  3;119,51,60;,
  3;51,60,60;,
  3;51,60,60;,
  3;51,60,60;,
  3;144,144,144;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,130,55;,
  3;60,93,60;,
  3;60,60,130;,
  3;60,60,130;,
  3;60,60,130;,
  3;60,93,130;,
  3;39,60,60;,
  3;39,60,122;,
  3;60,60,122;,
  3;60,60,122;,
  3;60,60,122;,
  3;60,60,122;,
  3;122,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;60,60,55;,
  3;51,46,129;,
  3;46,125,71;,
  3;71,125,69;,
  3;69,125,80;,
  3;80,125,78;,
  3;125,136,78;,
  3;71,129,46;,
  3;125,83,136;,
  3;136,83,131;,
  3;131,83,86;,
  3;86,83,86;,
  3;86,83,91;,
  3;91,83,133;,
  3;133,83,132;,
  3;83,93,132;;
 }
 MeshTextureCoords {
  260;
  0.375000;0.750000;,
  0.437500;0.812500;,
  0.375000;0.812500;,
  0.437500;0.750000;,
  0.500000;0.875000;,
  0.437500;0.875000;,
  0.500000;0.812500;,
  0.437500;0.950000;,
  0.562500;0.812500;,
  0.375000;0.950000;,
  0.375000;1.000000;,
  0.500000;0.950000;,
  0.562500;0.875000;,
  0.625000;0.750000;,
  0.562500;0.750000;,
  0.125000;0.125000;,
  0.187500;0.125000;,
  0.187500;0.187500;,
  0.125000;0.187500;,
  0.437500;1.000000;,
  0.437500;0.625000;,
  0.375000;0.625000;,
  0.375000;0.562500;,
  0.437500;0.562500;,
  0.562500;0.950000;,
  0.625000;0.812500;,
  0.125000;0.250000;,
  0.187500;0.250000;,
  0.437500;0.500000;,
  0.375000;0.500000;,
  0.325000;0.187500;,
  0.325000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.187500;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.625000;0.950000;,
  0.625000;0.562500;,
  0.625000;0.625000;,
  0.562500;0.625000;,
  0.562500;0.562500;,
  0.437500;0.125000;,
  0.437500;0.187500;,
  0.375000;0.437500;,
  0.437500;0.437500;,
  0.375000;0.250000;,
  0.325000;0.250000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.812500;0.187500;,
  0.812500;0.125000;,
  0.875000;0.125000;,
  0.875000;0.187500;,
  0.437500;0.250000;,
  0.875000;0.250000;,
  0.812500;0.250000;,
  0.375000;0.678050;,
  0.375000;0.620340;,
  0.406030;0.678050;,
  0.437500;0.300000;,
  0.375000;0.300000;,
  0.178630;0.071950;,
  0.178630;0.129660;,
  0.153430;0.071950;,
  0.562500;0.437500;,
  0.375000;0.500000;,
  0.441020;0.620340;,
  0.178630;0.250000;,
  0.125000;0.129660;,
  0.286430;0.071950;,
  0.253130;0.129660;,
  0.253130;0.071950;,
  0.503900;0.678050;,
  0.503900;0.620340;,
  0.531660;0.678050;,
  0.125000;0.250000;,
  0.441020;0.500000;,
  0.253130;0.250000;,
  0.503900;0.500000;,
  0.562970;0.678050;,
  0.562970;0.620340;,
  0.592120;0.678050;,
  0.625000;0.437500;,
  0.375000;0.446370;,
  0.441020;0.446370;,
  0.323990;0.129660;,
  0.562500;0.125000;,
  0.625000;0.125000;,
  0.625000;0.187500;,
  0.562500;0.187500;,
  0.441020;0.371870;,
  0.375000;0.371870;,
  0.562970;0.500000;,
  0.625000;0.620340;,
  0.675000;0.125000;,
  0.675000;0.187500;,
  0.323990;0.250000;,
  0.408820;0.066760;,
  0.375000;0.129660;,
  0.375000;0.066760;,
  0.503900;0.446370;,
  0.846570;0.071950;,
  0.821370;0.129660;,
  0.821370;0.071950;,
  0.786360;0.071950;,
  0.625000;0.500000;,
  0.473230;0.066760;,
  0.441020;0.129660;,
  0.441020;0.066760;,
  0.375000;0.250000;,
  0.503900;0.371870;,
  0.441020;0.301010;,
  0.375000;0.301010;,
  0.875000;0.129660;,
  0.821370;0.250000;,
  0.562970;0.446370;,
  0.875000;0.250000;,
  0.562970;0.371870;,
  0.562500;0.250000;,
  0.625000;0.250000;,
  0.625000;0.446370;,
  0.746870;0.129660;,
  0.503900;0.301010;,
  0.503900;0.129660;,
  0.441020;0.250000;,
  0.562970;0.066760;,
  0.562970;0.129660;,
  0.532710;0.066760;,
  0.675000;0.250000;,
  0.709310;0.071950;,
  0.676010;0.129660;,
  0.676010;0.071950;,
  0.594740;0.066760;,
  0.625000;0.371870;,
  0.746870;0.250000;,
  0.503900;0.250000;,
  0.562970;0.301010;,
  0.562500;0.300000;,
  0.562970;0.250000;,
  0.625000;0.300000;,
  0.676010;0.250000;,
  0.625000;0.129660;,
  0.625000;0.301010;,
  0.625000;0.250000;,
  0.375000;0.875000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.187500;0.075000;,
  0.125000;0.075000;,
  0.375000;0.675000;,
  0.437500;0.675000;,
  0.500000;0.750000;,
  0.250000;0.000000;,
  0.250000;0.075000;,
  0.500000;0.675000;,
  0.325000;0.000000;,
  0.325000;0.075000;,
  0.250000;0.125000;,
  0.562500;0.675000;,
  0.500000;0.625000;,
  0.375000;0.000000;,
  0.375000;0.075000;,
  0.500000;1.000000;,
  0.250000;0.187500;,
  0.625000;0.675000;,
  0.625000;0.875000;,
  0.500000;0.562500;,
  0.437500;0.000000;,
  0.437500;0.075000;,
  0.812500;0.075000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.875000;0.075000;,
  0.500000;0.075000;,
  0.500000;0.000000;,
  0.250000;0.250000;,
  0.500000;0.500000;,
  0.750000;0.075000;,
  0.750000;0.000000;,
  0.562500;0.075000;,
  0.562500;0.000000;,
  0.500000;0.125000;,
  0.675000;0.075000;,
  0.675000;0.000000;,
  0.375000;0.375000;,
  0.437500;0.375000;,
  0.750000;0.125000;,
  0.625000;0.075000;,
  0.625000;0.000000;,
  0.500000;0.437500;,
  0.500000;0.187500;,
  0.750000;0.187500;,
  0.441020;0.678050;,
  0.218120;0.071950;,
  0.474350;0.678050;,
  0.230530;0.071950;,
  0.500000;0.678050;,
  0.500000;0.250000;,
  0.323990;0.071950;,
  0.625000;0.678050;,
  0.750000;0.250000;,
  0.450750;0.315900;,
  0.458740;0.300000;,
  0.453170;0.311100;,
  0.351030;0.071950;,
  0.371950;0.071950;,
  0.562500;0.375000;,
  0.625000;0.375000;,
  0.503900;0.066760;,
  0.746870;0.071950;,
  0.549250;0.315900;,
  0.546830;0.311100;,
  0.541260;0.300000;,
  0.648970;0.071950;,
  0.625000;0.066760;,
  0.628050;0.071950;,
  0.144800;0.071950;,
  0.125000;0.071950;,
  0.341970;0.071950;,
  0.875000;0.071950;,
  0.855200;0.071950;,
  0.769470;0.071950;,
  0.500000;0.066760;,
  0.658030;0.071950;,
  0.445960;0.402520;,
  0.445960;0.375000;,
  0.445960;0.381580;,
  0.452350;0.415890;,
  0.454540;0.420460;,
  0.445960;0.325440;,
  0.445960;0.345350;,
  0.445960;0.363010;,
  0.545460;0.420460;,
  0.547650;0.415890;,
  0.554040;0.402520;,
  0.554040;0.383960;,
  0.554040;0.375000;,
  0.554040;0.325440;,
  0.554040;0.363010;,
  0.554040;0.343100;,
  0.459550;0.430960;,
  0.466580;0.430960;,
  0.474500;0.430960;,
  0.488910;0.430960;,
  0.500000;0.430960;,
  0.501690;0.430960;,
  0.513690;0.430960;,
  0.527220;0.430960;,
  0.533440;0.430960;,
  0.540450;0.430960;,
  0.459550;0.298380;,
  0.467210;0.298380;,
  0.474500;0.298380;,
  0.488430;0.298380;,
  0.500000;0.298380;,
  0.501690;0.298380;,
  0.514140;0.298380;,
  0.527220;0.298380;,
  0.534000;0.298380;,
  0.540450;0.298380;;
 }
}
