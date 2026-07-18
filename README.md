# Attraction Manager (C)

연결 리스트(linked list)로 구현한 놀이기구 관리 콘솔 프로그램.

## 기능

- `attractionlist.dat` 파일에서 놀이기구 목록 로드
- 놀이기구 추가 / 이름으로 검색 / 삭제 / 전체 출력
- limit 기준 오름차순 **삽입 정렬** (`sortedInsert_l`, `insertSort_l`)
- 메뉴 기반 콘솔 인터페이스

## 데이터 형식

```
이름 limit time
청룡열차 20 5
회전목마 35 7
```

## 구조

| 파일 | 내용 |
|---|---|
| [mypro.c](mypro.c) | 전체 구현 — `attraction` 구조체 연결 리스트, 정렬 삽입, 메뉴 처리 |
| [attractionlist.dat](attractionlist.dat) | 놀이기구 데이터 파일 |
| [makefile](makefile) | 빌드 스크립트 |

## 빌드 & 실행

```bash
make        # gcc -o mypro mypro.c
./mypro
make clean
```
