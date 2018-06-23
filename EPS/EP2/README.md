# CUDA

Para executar a comunicação entre device e host com eficiência, adotamos uma
abordagem que sempre cria blocos de 2048 matrizes, isto é, se houver menos do
que essa quantidade, haverá uma parcela do bloco com matrizes "dummy".
Além disso, o armazenamento da leitura não é feito de modo tradicional. Para
explicar o modo de armazenamento, suponha o exemplo com 3 matrizes 3x3, A, B e C.
Para isso, haverá 2045 matrizes 3x3 "dummy", Di, com i = 1, 2, ..., 2045. Então,
armazenamos da seguinte forma:

[
    A(1,1), B(1,1), C(1,1), D1(1,1), D2(1,1), ..., D2044(1,1), D2045(1,1), 
    A(1,2), B(1,2), C(1,2), D1(1,2), ..., D2045(1,2) ...
    A(3,3), B(3,3), C(3,3) D1(3,3), ..., D2045(3,3)
]

Este vetor então é passado para o device. Um fator relevante de se destacar é 
que, dentro do device, foi utilizada a memória compartilhada, uma vez que essa
se mostrou a melhor opção. Então são lançadas 1024 threads no device,
cada uma responsável pela redução de um bloco, que paulatinamente vai reduzindo.
Ou seja, 1024 threads resolvem, cada uma, um par, depois 512 thread resolvem,
cada uma, outro par, e assim por diante, até que tenha sido reduzido o bloco
em questão. 
