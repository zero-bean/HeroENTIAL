# HeroENTIAL
[Portfolio] C++, WIN32를 기반한 싱글 RPG 게임

- 완성하면 나중에 PPT에 정리해서 넣을 예정 -

* 해결한 오류 목록
1. [Collision Manager: 2가지의 원인이 오류를 일으켰다]
Update에서 Collider를 vector에 넣어 추가, 삭제, 실행 등을 한 번에 운용했다는 점이다. 삭제와 추가는 Queue를 통해 관리하고, 충돌 끼리의 검사는 vector를 통해 관리하는 것으로 해결함.
Collider는 _collisionMap을 통해서 다른 Collider과 충돌 여부를 확인하는데, shared_ptr로 추가하여 순환 참조 문제가 발생함. weak_ptr로 변경하여 해결함.
+ Manager 및 Scene들의 생명 주기를 (삭제 - 업데이트 - 추가) 구조로 변경하여 danglin pointer 방지.

2. [Player가 피격 과정에서 강제로 이동하는 오류]
이동 거리의 괴리에 관한 보정을 하고 이동한 거리 만큼 감소하는 부분을 추가함.

3. [Texture, Flipbook - nullptr]
해당 Scene 혹은 Object에서 ResourceManager를 통해 해당 파일을 로드하는 코드를 누락했는지 확인할 것.

4. [Scene 전환 시 UI가 비정상적인 위치에서 렌더링 되는 오류]
UIManager에게 BeginPlay 추가 및 SceneManager에서 같이 Update, Render, Clear 하도록 수정함.

5. [프레임 드랍 현상]
SpriteActor의 Render에 사용되는 함수가 TransparentBlt였는데, 이 기능이 리소스를 많이 사용하는 것이 원인.
BitBlt로 변경하는 것으로 갈음.

6. [Scene 전환에서 플레이어 스프라이트가 등록되지 않는 현상]
ResourceManager는 unordered_map을 통해서 관리하는데, 로드 과정에서 잔류한 파일과 collision이 발생하는 것이 원인.
Scene을 Clear할 때, ResourceManager도 Clear하도록 구조를 변경하여 해결함.

* 코드 리팩터링 목록
1. [Remove 함수들 개선]
Manager 단위의 클래스가 관리하던 (추가 - 업데이트 - 삭제) 코드를 개선함
변경 전에는 삭제를 할 때 v.erase(std::remove(v.begin(), v.end(), target), v.end()); 를 사용함.
그러나 이 코드는 삭제를 하면 모든 원소를 한칸씩 앞으로 당겨 O(N) 오버헤드가 발생하게 됨.
			iter_swap(it, prev(_uis.end()));
			_uis.pop_back();
하지만 삭제할 대상을 맨 뒤로 스왑하여 삭제하는 것으로 바꾸어 O(1)로 줄이게 바꿈.

2. 플레이어와 인벤토리 기능 분리
기존에는 인벤토리 등 게임 데이터 관련 기능이 Player 클래스에 포함되어 있었지만,
이는 Player의 본래 책임인 조작 및 상호작용 기능과는 분리되어야 한다고 판단함.
Player는 씬에 따라 생성/파괴되는 일시적인 객체인 반면, 인벤토리는 지속적으로 유지되는 데이터이기 때문임.
따라서 인벤토리 및 퀘스트 등 게임 데이터 전반은 GameManager에서 통합적으로 관리하도록 리팩토링하고,
이를 통해 씬과 무관하게 일관된 데이터 유지 및 접근이 가능해짐.