#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QWidget>
#include <QMessageBox>
#include <QMap>
#include <QList>
#include <QString>
#include <QGroupBox>

// =========================================================================
// [데이터 구조 정의] 
// 항공편 및 공항 네트워크(그래프)를 표현하기 위한 구조체
// =========================================================================

// 항공편 정보를 저장하는 구조체
struct FlightInfo {
    QString flightNumber; // 항공편 번호 (예: "LJ302")
    QString airline;      // 운항 항공사 이름 (예: "진에어")
    int price;            // 항공권 가격 (원화)
    QString duration;     // 비행 소요 시간 (예: "1시간 0분")
};

// 그래프의 간선(Edge)을 표현하는 구조체
// 출발지 공항에서 특정 '목적지 공항'으로 가는 노선과 해당 노선의 항공편 목록을 관리
struct AirportEdge {
    QString toAirport;         // 연결된 목적지 공항 코드 (Vertex)
    QList<FlightInfo> flights; // 해당 노선에 존재하는 항공편 리스트
};

// =========================================================================
// [데이터 관리 클래스] 
// 인접 리스트(Adjacency List) 방식을 이용한 공항 네트워크 그래프
// =========================================================================
class AirportGraph {
private:
    // Key: 출발 공항 코드, Value: 출발 공항에서 갈 수 있는 목적지 노선(간선) 목록
    QMap<QString, QList<AirportEdge>> adjList;

public:
    // 생성자: 시스템에서 사용할 초기 공항 및 항공편 노선 데이터 등록
    AirportGraph() {
        // 1. 제주(CJU) 출발 노선
        adjList["CJU"].append(AirportEdge{"GMP", {{"LJ302", "진에어", 85000, "1시간 0분"}}});
        adjList["CJU"].append(AirportEdge{"PUS", {{"LJ301", "진에어", 75000, "0시간 50분"}}});
        adjList["CJU"].append(AirportEdge{"NRT", {{"TW711", "티웨이항공", 240000, "2시간 20분"}}});

        // 2. 런던 히드로(LHR) 출발 노선
        adjList["LHR"].append(AirportEdge{"ICN", {{"QA101", "월드항공", 450000, "3시간 00분"}}});
        adjList["LHR"].append(AirportEdge{"CDG", {{"BA304", "영국항공", 120000, "1시간 15분"}}});
        adjList["LHR"].append(AirportEdge{"DXB", {{"EK002", "에미레이트", 750000, "7시간 0분"}}});

        // 3. 미국 지역(JFK, LAX) 출발 노선
        adjList["JFK"].append(AirportEdge{"LHR", {{"VS102", "버진아틀란틱", 680000, "7시간 30분"}}});
        adjList["JFK"].append(AirportEdge{"LAX", {{"AA201", "아메리칸항공", 310000, "5시간 40분"}}});
        adjList["LAX"].append(AirportEdge{"ICN", {{"OZ201", "아시아나항공", 1250000, "11시간 20분"}}});

        // 4. 아시아 주요 공항(ICN, PEK, GMP) 출발 노선
        adjList["ICN"].append(AirportEdge{"NRT", {{"7C1102", "제주항공", 280000, "2시간 15분"}}});
        adjList["ICN"].append(AirportEdge{"PEK", {{"CA124", "중국국제항공", 210000, "2시간 0분"}}});
        adjList["PEK"].append(AirportEdge{"DXB", {{"EK307", "에미레이트", 890000, "8시간 35분"}}});
        adjList["GMP"].append(AirportEdge{"CJU", {{"KE1201", "대한항공", 95000, "1시간 5분"}}});

        // 5. 기타 지역(SGN, SYD) 출발 노선
        adjList["SGN"].append(AirportEdge{"SYD", {{"VN773", "베트남항공", 520000, "8시간 15분"}}});
        adjList["SYD"].append(AirportEdge{"ICN", {{"QF087", "콰타스항공", 980000, "10시간 0분"}}});
    }

    // 특정 공항에서 출발하는 항공편 검색 (출발 노선 조회)
    QList<std::pair<QString, FlightInfo>> getDeparturesFrom(const QString& airportCode) {
        QList<std::pair<QString, FlightInfo>> result;
        if (adjList.contains(airportCode)) {
            for (const auto& edge : adjList[airportCode]) {
                for (const auto& flight : edge.flights) {
                    result.append({edge.toAirport, flight});
                }
            }
        }
        return result;
    }

    // 특정 공항으로 들어오는 항공편 검색 (도착 노선 조회)
    QList<std::pair<QString, FlightInfo>> getArrivalsTo(const QString& airportCode) {
        QList<std::pair<QString, FlightInfo>> result;
        for (auto it = adjList.begin(); it != adjList.end(); ++it) {
            QString fromAirport = it.key();
            for (const auto& edge : it.value()) {
                if (edge.toAirport == airportCode) {
                    for (const auto& flight : edge.flights) {
                        result.append({fromAirport, flight});
                    }
                }
            }
        }
        return result;
    }
};

// =========================================================================
// [메인 UI 윈도우 클래스] 
// 지도를 표시하고 항공권 조회 및 예매 인터페이스를 제공하는 메인 창
// =========================================================================
class MainWindow : public QMainWindow {
    Q_OBJECT // Qt 메타 객체 시스템(시그널/슬롯) 활성화 매크로

private:
    // QListWidget 아이템에 커스텀 데이터를 안전하게 저장하기 위한 고유 역할(Role) 정의
    enum FlightRole {
        RoleFlightNum = Qt::UserRole,
        RoleAirline,
        RoleFromRoute,
        RoleToRoute,
        RolePrice,
        RoleDuration
    };

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // 기본 윈도우 타이틀 및 크기 설정
        setWindowTitle("항공권 조회 및 예매 프로그램");
        resize(1200, 650);

        // 어두운 테마 스카이 블루/연두 포인트 스타일시트 적용
        setStyleSheet(
            "QMainWindow { background-color: #0c0c0c; } "
            "QGroupBox { color: white; font-weight: bold; border: 1px solid #333; margin-top: 10px; } "
            "QListWidget { background-color: #16161a; color: #cbd5e1; border: 1px solid #2a2a35; font-size: 13px; padding: 5px; border-radius: 4px; } "
            "QListWidget::item:hover { background-color: #2563eb; color: white; } "
            "QLabel { color: white; font-family: 'Malgun Gothic', sans-serif; }"
        );

        auto* central = new QWidget(this);
        setCentralWidget(central);
        auto* mainLayout = new QHBoxLayout(central);

        // -----------------------------------------------------------------
        // [왼쪽 영역] 세계 지도 및 공항 버튼 배치
        // -----------------------------------------------------------------
        auto* mapContainer = new QWidget(this);
        mapContainer->setFixedSize(750, 480);

        imageLabel = new QLabel(mapContainer);
        QPixmap pixmap("sample.jpg"); // 실행 파일 경로에 세계지도 이미지 파일 필요

        if (pixmap.isNull()) {
            // 이미지 로드 실패 시 대체 텍스트 및 기본 배경 출력
            imageLabel->setText("<h3 style=color:red; text-align:center;><br><br>지도 이미지(sample.jpg) 로드 실패</h3>");
            imageLabel->setFixedSize(750, 480);
            imageLabel->setStyleSheet("background-color:#1e1e24; border:1px solid #333; border-radius:6px;");
        } else {
            // 이미지 크기를 레이블에 맞게 부드럽게 조정하여 출력
            imageLabel->setPixmap(pixmap.scaled(750, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            imageLabel->setGeometry(0, 0, 750, 480);
        }

        // 지도 위 주요 공항 위치 좌표(x, y)에 맞춰 버튼 생성
	createAirportButton(mapContainer, "LAX", 185, 145); // 북아메리카 서부 (로스앤젤레스 육지)
	createAirportButton(mapContainer, "JFK", 245, 125); // 북아메리카 동부 (뉴욕 육지)
	createAirportButton(mapContainer, "LHR", 370, 85);  // 유럽 영국 (런던 히드로)
	createAirportButton(mapContainer, "CDG", 385, 95);  // 유럽 프랑스 (파리 샤를드골)
	createAirportButton(mapContainer, "DXB", 480, 165); // 중동 (두바이 사우디 반도)
	createAirportButton(mapContainer, "PEK", 560, 135); // 아시아 중국 (베이징 육지)
	createAirportButton(mapContainer, "ICN", 590, 140); // 아시아 한국 (인천 육지)
	createAirportButton(mapContainer, "NRT", 620, 140); // 아시아 일본 (나리타 섬)
	createAirportButton(mapContainer, "CJU", 590, 165); // 아시아 한국 (제주 섬)
	createAirportButton(mapContainer, "SGN", 565, 205); // 아시아 베트남 (호치민 육지)
	createAirportButton(mapContainer, "SYD", 615, 305); // 호주 (시드니 호주 대륙 안쪽)

        mainLayout->addWidget(mapContainer, 0, Qt::AlignVCenter);

        // -----------------------------------------------------------------
        // [오른쪽 영역] 선택된 공항의 항공편 리스트 정보창
        // -----------------------------------------------------------------
        auto* rightLayout = new QVBoxLayout();

        statusLabel = new QLabel(
            "<h2 style='color:#38bdf8;'>공항을 클릭하세요</h2>"
            "<span style='color:#94a3b8;'>좌측 노선도에서 공항을 선택해 주세요.</span>"
        );
        rightLayout->addWidget(statusLabel);

        // 출발 항공편 섹션
        rightLayout->addWidget(new QLabel("<b style='color:#a3e635;'>✈️ 출발 항공편</b> (클릭 시 예매)"));
        depListWidget = new QListWidget();
        rightLayout->addWidget(depListWidget);

        // 도착 항공편 섹션
        rightLayout->addWidget(new QLabel("<b style='color:#38bdf8;'>🛬 도착 항공편</b> (클릭 시 예매)"));
        arrListWidget = new QListWidget();
        rightLayout->addWidget(arrListWidget);

        mainLayout->addLayout(rightLayout);

        // 리스트 아이템 클릭 시 예매를 처리할 슬롯 함수 연결
        connect(depListWidget, &QListWidget::itemClicked, this, &MainWindow::handleBooking);
        connect(arrListWidget, &QListWidget::itemClicked, this, &MainWindow::handleBooking);
    }

private slots:
    // 리스트 항목 클릭 시 예매 확인창을 띄워주는 슬롯 함수
    void handleBooking(QListWidgetItem* item) {
        if (!item) return;

        // [방어 코드] "항공편이 없습니다" 등의 안내 문구를 클릭한 경우 처리 안 함
        if (item->data(RoleFlightNum).isNull())
            return;

        // 아이템 내부 MetaData에서 비행 정보 복원
        QString flightNum = item->data(RoleFlightNum).toString();
        QString airline   = item->data(RoleAirline).toString();
        QString fromRoute = item->data(RoleFromRoute).toString();
        QString toRoute   = item->data(RoleToRoute).toString();
        int price         = item->data(RolePrice).toInt();
        QString duration  = item->data(RoleDuration).toString();

        // 예매 성공 알림 메시지 박스 생성 및 커스텀 스타일링
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("예매 완료");

        QString content = QString(
            "<b>예매가 완료되었습니다.</b><br><br>"
            "항공편: %1 (%2)<br>"
            "구간: %3 → %4<br>"
            "가격: ₩%5<br>"
            "소요 시간: %6"
        ).arg(flightNum).arg(airline).arg(fromRoute).arg(toRoute).arg(QString::number(price)).arg(duration);

        msgBox.setText(content);
        msgBox.setStyleSheet(
            "QMessageBox { background-color:#1c1917; border:1px solid #444; }"
            "QLabel { color:#e7e5e4; font-size:13px; }"
            "QPushButton { background-color:#2563eb; color:white; font-weight:bold; width:75px; height:26px; border-radius:3px; }"
        );
        msgBox.exec();
    }

private:
    QLabel* imageLabel;
    QLabel* statusLabel;
    QListWidget* depListWidget;
    QListWidget* arrListWidget;
    AirportGraph airportGraph;

    // 지도 위에 배치될 공항 버튼을 생성하고 클릭 이벤트를 바인딩하는 함수
    void createAirportButton(QWidget* parent, const QString& code, int x, int y) {
        auto* btn = new QPushButton(code, parent);
        btn->setGeometry(x, y, 46, 23);
        
        btn->setStyleSheet(
            "QPushButton { background-color:#2563eb; color:white; font-weight:bold; border:1px solid #1d4ed8; border-radius:3px; font-size:10px; }"
            "QPushButton:hover { background-color:#1d4ed8; }"
        );

        // 버튼 클릭 시 람다식을 통해 특정 공항의 정보 갱신
        connect(btn, &QPushButton::clicked, this, [this, code]() {
            // 상단 상태 타이틀 업데이트
            statusLabel->setText(QString(
                "<h2 style='color:#38bdf8;'>%1 (%2)</h2>"
                "<span style='color:#94a3b8;'>아래 항공권을 클릭하면 예매가 진행됩니다.</span>"
            ).arg(code).arg(getAirportName(code)));

            // 1. 출발 항공편 리스트 갱신
            depListWidget->clear();
            auto departures = airportGraph.getDeparturesFrom(code);
            for(const auto& p : departures) {
                QString txt = QString(" [%1] %2\n 구간: %3 → %4\n 가격: ₩%5 | 소요시간: %6")
                                .arg(p.second.flightNumber).arg(p.second.airline).arg(code).arg(p.first)
                                .arg(QString::number(p.second.price)).arg(p.second.duration);

                auto* item = new QListWidgetItem(txt);
                // 커스텀 열거형(Enum) 데이터 매핑 적용
                item->setData(RoleFlightNum, p.second.flightNumber);
                item->setData(RoleAirline, p.second.airline);
                item->setData(RoleFromRoute, code);
                item->setData(RoleToRoute, p.first);
                item->setData(RolePrice, p.second.price);
                item->setData(RoleDuration, p.second.duration);
                item->setSizeHint(QSize(0, 65)); // 가독성을 위해 항목 높이 조절
                depListWidget->addItem(item);
            }
            if(departures.isEmpty()) {
                depListWidget->addItem(new QListWidgetItem(" 해당 공항에서 출발하는 항공편이 없습니다."));
            }

            // 2. 도착 항공편 리스트 갱신
            arrListWidget->clear();
            auto arrivals = airportGraph.getArrivalsTo(code);
            for(const auto& p : arrivals) {
                QString txt = QString(" [%1] %2\n 구간: %3 → %4\n 가격: ₩%5 | 소요시간: %6")
                                .arg(p.second.flightNumber).arg(p.second.airline).arg(p.first).arg(code)
                                .arg(QString::number(p.second.price)).arg(p.second.duration);

                auto* item = new QListWidgetItem(txt);
                // 커스텀 열거형(Enum) 데이터 매핑 적용
                item->setData(RoleFlightNum, p.second.flightNumber);
                item->setData(RoleAirline, p.second.airline);
                item->setData(RoleFromRoute, p.first);
                item->setData(RoleToRoute, code);
                item->setData(RolePrice, p.second.price);
                item->setData(RoleDuration, p.second.duration);
                item->setSizeHint(QSize(0, 65)); 
                arrListWidget->addItem(item);
            }
            if(arrivals.isEmpty()) {
                arrListWidget->addItem(new QListWidgetItem(" 해당 공항으로 들어오는 항공편이 없습니다."));
            }
        });
    }

    // 공항 코드(IATA)를 한글 이름으로 매핑해주는 헬퍼 함수
    QString getAirportName(const QString& code) {
        static QMap<QString, QString> names = {
            {"ICN", "인천국제공항"}, {"CJU", "제주국제공항"}, {"GMP", "김포국제공항"},
            {"LHR", "런던 히드로"},   {"CDG", "파리 샤를드골"}, {"DXB", "두바이국제공항"},
            {"LAX", "로스앤젤레스"}, {"JFK", "뉴욕 JFK"},     {"PEK", "베이징 수도공항"},
            {"SGN", "호치민 탄손누트"}, {"SYD", "시드니공항"}, {"NRT", "도쿄 나리타"}
        };
        return names.value(code, "국제공항");
    }
};