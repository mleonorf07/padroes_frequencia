#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char** argv) {
    // 1. Carregar a imagem: por omissão "image.jpg", ou o nome passado na linha de comandos
    //    Exemplo: ./build/paleta outra_foto.jpg
    std::string nome = (argc > 1) ? argv[1] : "image.jpg";
    cv::Mat img = cv::imread(nome);

    if (img.empty()) {
        std::cout << "Erro: Nao foi possivel carregar a imagem '" << nome << "'!" << std::endl;
        return -1;
    }

    // 2. Definir a paleta fixa de cores (em formato BGR: Azul, Verde, Vermelho)
    std::vector<cv::Vec3b> palette = {
        { 0, 0, 0 },       // Preto
        { 255, 255, 255 }, // Branco
        { 255, 0, 0 },     // Azul puro
        { 0, 0, 255 },     // Vermelho puro
        { 0, 255, 0 }      // Verde puro
    };

    // 3. Percorrer cada linha e cada coluna (cada pixel) da imagem
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            cv::Vec3b& pixel = img.at<cv::Vec3b>(y, x);

            int bestIndex = 0;
            double minDistance = -1;

            // 4. Comparar o pixel com cada cor da paleta para encontrar a mais proxima
            for (size_t i = 0; i < palette.size(); i++) {
                double b_diff = (double)pixel[0] - palette[i][0];
                double g_diff = (double)pixel[1] - palette[i][1];
                double r_diff = (double)pixel[2] - palette[i][2];
                double distance = std::sqrt(b_diff * b_diff + g_diff * g_diff + r_diff * r_diff);

                if (minDistance == -1 || distance < minDistance) {
                    minDistance = distance;
                    bestIndex = (int)i;
                }
            }

            // 5. Substituir a cor do pixel pela cor escolhida da paleta
            pixel = palette[bestIndex];
        }
    }

    // 6. Mostrar o resultado numa janela redimensionavel e guardar em PNG (sem perdas)
    cv::namedWindow("Paleta Limitada - Ponto 1", cv::WINDOW_NORMAL);
    cv::imshow("Paleta Limitada - Ponto 1", img);
    cv::imwrite("resultado_ponto1.png", img);

    std::cout << "Processamento concluido com sucesso! Pressiona qualquer tecla para fechar." << std::endl;
    cv::waitKey(0);

    return 0;
}
