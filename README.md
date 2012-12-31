Code Examples which show how to use Rcpp package
--

If you want to build more than one .cpp and .h files in Rcpp, you can use Rcpp.package.skelton() with RStudio.

[課題]
sourceCpp()で複数のファイルからなるC++の関数・クラス群をコンパイルしようとすると, エラーが出る.
 
[解決策]
簡単な解決策としては, パッケージを作成することがある.
RStudioのパッケージ開発機能を用いれば簡単にできる.
RStudioでRcpp を使用するProject を作って, srcディレクトリ内に通常のC++のやり方でcpp, h ファイルを作成してやればよい.
Buildからふつうにビルド出来る.
