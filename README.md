# HeroENTIAL
[Portfolio] C++, WIN32를 기반한 싱글 RPG 게임

* 해결한 오류 목록
1. Collision Manager: 2가지의 원인이 오류를 일으켰다. 
1-A. Update에서 Collider를 vector에 넣어 추가, 삭제, 실행 등을 한 번에 운용했다는 점이다. 삭제와 추가는 Queue를 통해 관리하고, 충돌 끼리의 검사는 vector를 통해 관리하는 것으로 해결함.
1-B. Collider는 _collisionMap을 통해서 다른 Collider과 충돌 여부를 확인하는데, shared_ptr로 추가하여 순환 참조 문제가 발생함. weak_ptr로 변경하여 해결함.

2. Player가 피격 과정에서 강제로 이동하는 오류
2-A. 이동 거리의 괴리에 관한 보정하는 부분을 추가함.
2-B. 이동한 거리 만큼 감소하는 부분을 추가함.

3. Texture, Flipbook - nullptr
2-A. 해당 Scene 혹은 Object에서 ResourceManager를 통해 해당 파일을 로드하는 코드를 누락했는지 확인할 것.

4. Scene 전환 시 UI가 비정상적인 위치에서 렌더링 되는 오류
4-A. 각 UI의 초기화 부분의 위치를 생성자에서 BeginPlay로 옮김 => UIManager의 처리 부분을 Scene으로 옮기는 것으로 바꿀 예정 
(문제가 생긴다면.. 아마 생길 확률이 높음)

5. 프레임 드랍 현상
5-A. SpriteActor의 Render에 사용되는 함수가 TransparentBlt였는데, 이 기능이 리소스를 많이 사용함.
    따라서 BitBlt로 변경하여 프레임 개선함.

6 => 인벤토리 패널의 슬롯 구조를 해결해야 함