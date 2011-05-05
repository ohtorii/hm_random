乱数を生成する秀丸マクロ。


■はじめに
    秀丸エディタで乱数を生成するマクロがなかったので自作しました。
    （浮動小数点版の秀丸エディタにはあるようですが、当方は普通の秀丸エディタな
      ので。）


■出来ること
    ＊生成する乱数の個数指定

    ＊乱数の種類
        sfmt(SIMD-oriented Fast Mersenne Twister.)
        xorshift
        xor
        xor64
        xorwow
        drand48

    ＊最小値の指定

    ＊最大値の指定

    ＊プレフィックスの指定

    ＊出力乱数の基数を指定
        2
        10
        16

    ＊区切り文字の指定
        改行
        カンマ
        空白

    上記項目をダイアログで設定すると新しい秀丸エディタが開き乱数が追加されます。
    カスタマイズは可能です後述の「カスタマイズ」を参照。


■ファイル構成
    hm_random_menu.mac          メニューから生成する乱数を選択するマクロ
    hm_random_sample_1.mac      カスタマイズするためのサンプルマクロ（その１）
    hm_random_sample_2.mac      カスタマイズするためのサンプルマクロ（その２）
    hm_random_main.mac          内部利用のマクロ
    hm_random.exe               乱数を生成する実行ファイル


■インストール
    （Step1）
    このマクロは「田楽DLL」が必要です、必ずインストールして下さい。
    http://www.ceres.dti.ne.jp/~sugiura/

    （Step2）
    ファイルを全て秀丸エディタのマクロディレクトリへコピーして下さい。

    （Step3）
    「秀丸エディタのメニュー → マクロ → マクロ実行」を選択し、
    hm_random_menu.mac を実行してください。

    （Step4）
    ダイアログが起動するので設定を行いOKボタンを押すと、新しい秀丸が開き生成し
    た乱数が追加されます。


■パフォーマンス
    自分のPCでは10秒で5万個の乱数を生成できました。
    乱数の生成自体は一瞬で終わりますが、標準入力を秀丸エディタへ反映するのに時
    間がかかります。


■カスタマイズ（プログラマ向け）
    下記マクロを参照して下さい。
        hm_random_sample_1.mac
        hm_random_sample_2.mac

    2行のマクロなので分かるかと思います。


■xorshiftについて
    論文中の間違いは修正して反映しています。
    詳細はソースコードを参照して下さい。


■References
    Xorshift RNGs, George Marsaglia, The Florida State University.
    http://www.jstatsoft.org/v08/i14/

    SIMD-oriented Fast Mersenne Twister (SFMT).
    http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/index-jp.html

    drand48
    http://www001.upp.so-net.ne.jp/isaku/index.html


■連絡先
    http://d.hatena.ne.jp/ohtorii
    https://github.com/ohtorii


以上
