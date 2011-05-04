乱数を生成する秀丸マクロ。


■はじめに
	秀丸エディタで乱数を生成するマクロがなかったので自作しました。
	（浮動小数点版の秀丸エディタにはあるようですが、当方は普通の秀丸エディタなので）


■出来ること
	・生成する乱数の個数
	・乱数の種類（xorshift/Mersenne Twister）
	・基数(10/16)
	・整数の型(uint8/sint8/uint16/sint16/uint32/sint32/uint64/sint64)

	上記項目をダイアログで設定すると新しい秀丸エディタが開き乱数が追加されます。
	
	
■乱数の種類
	・xorshift
		xor128
		xor
		xore64
		xorwow
	・SFMT(SIMD-oriented Fast Mersenne Twister.)


■ファイル構成
	hm_random_menu.mac			メニューから乱数を選択するマクロ
	hm_random_sample_1.mac		カスタマイズするためのサンプルマクロ
	hm_random_sample_2.mac		カスタマイズするためのサンプルマクロ
	hm_random_main.mac			内部利用のマクロ
	hm_random.exe				乱数を生成する実行ファイル


■インストール
	ファイルを全て秀丸エディタのマクロディレクトリへコピーして下さい。
	
	「秀丸エディタのメニュー → マクロ → マクロ実行」を選択し、
	hm_random_menu.mac を実行してください。
	
	ダイアログが起動するので設定を行いOKボタンを押すと、新しい秀丸が開き生成した乱数が追加されます。
	

■パフォーマンス
	
	

■カスタマイズ
	下記マクロを参照して下さい。
		hm_random_sample_1.mac 
		hm_random_sample_2.mac
	
	2行のマクロなので分かるかと思います。
	
	
■連絡先
	http://d.hatena.ne.jp/ohtorii
    https://github.com/ohtorii


以上