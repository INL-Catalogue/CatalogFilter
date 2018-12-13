# CatalogFilter
## 概要
- B4卒論研究
- 既存のフィルタは全体から好みの属性のみに焦点を合わせる
- ユーザ毎に好みに合わないものを削除するフィルタリングを作成
  - カタログ関係を表したcsvファイルからノードデータを読み取り
  - 初期計算を行いグラフ全体をスコアリング
  - このスコアリング結果をユーザ毎に取り出してフィルタ処理を行う
- データベースはMySQL5.7，実装はC++を使用
## 前提
- カタログ内のグラフのトポロジはフルメッシュ
## 初期計算
- 全てのノードのスコア初期値を100にする
- simplified PageRankアルゴリズムによる反復計算
- 各ノードのスコア更新差分n以下（e.g., n=1）で計算終了
- 計算結果をデータベースへ保存
## フィルタの計算手法
1. PageRank like 計算
- フィルタを掛けたいコンテンツ（以下指定コンテンツ）のスコアを負号化
- simplified PageRankアルゴリズムによる反復計算
- 各ノードのスコア更新差分n以下で計算終了
- 指定コンテンツのスコアは最初に負号化したときの値を入れる
. エッジの重みを用いた計算
- 指定コンテンツのスコアを負号化
- 指定コンテンツとその隣接コンテンツとのエッジの重みの合計Wを計算
- i(score): 指定コンテンツのスコア
- n(score): 隣接コンテンツのスコア
- n.weight: 指定コンテンツと隣接コンテンツの間のエッジの重み
- 全ての隣接コンテンツに対して以下の計算
  - n(score) += i(score) * (n.weight / W)
## TODO
