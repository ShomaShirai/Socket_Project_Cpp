// Camera_capture.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <zmq.hpp>

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }

    // ZMQ setup
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);  // PUBLISHERソケットに変更
    socket.bind("tcp://*:5555");             // bindに変更

    cv::Mat frame;

    while (cap.read(frame))
    {
        // フレームをエンコード
        std::vector<uchar> encoded_frame;
        cv::imencode(".jpg", frame, encoded_frame);

        // エンコードされた画像データを送信
        socket.send(zmq::buffer(encoded_frame.data(), encoded_frame.size()), zmq::send_flags::none);

        const int key = cv::waitKey(1);
        if (key == 'q')
        {
            break;
        }
    }

    cap.release();
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//   1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
