# Что находится в данной директории?
Тут находятся диаграммы последовательности и их исходный код (PlantUML), которые представляют собой последовательность взаимодействий между объектами и компонентами системы в рамках определенного прецедента.

В последующих диаграммах используются следующие объекты и конструкции:
* **Actor** (представляют участников, которые взаимодействуют с системой)
* **Alt конструкция** (являются аналогами if-else)
* **Ref блок** (являются ссылками на другую часть диаграммы, в нашем случае используется для указания того, что может быть открыто одно из окон)
* **View** (представляют окна, с которыми взаимодействует пользователь)
* **Controller** (представляют некоторые процедуры, которые выполняет система)
* **Entity** (представляют сущности, которые являются постоянными и находятся вне нашей системы)

## Диаграмма последовательности для прецедента "Авторизация"
Исходный код находится в файле `auth.wsd`
![auth sequences diagram](https://www.plantuml.com/plantuml/svg/TLFDRjGm4BxxAKQBn8q3DzG3weaNu5e9UHC34Qa3ZdE0Kxi8AA9I1LS4VOLjgQaRY7c5yHln3OdeRjHUTkpP-NvcnjbjlNQ-swz9T_xvazQywemjZ5BjYyg-r4xlKscUwgxsZnhh7rTl3Dr_e9GkVEDemQUS-5S-val4Srxd5GUvBqYtrBN6ARLiEbjgznh5txddWHFncizHcV81Hxu4wZrY5Cnaed36MAMCzPKNu6SWK4TyWSF0G_wKt_qhBvTR0byvvW_oDryHzwWz0t50OaNGWjD9fT3BoXe_2T6TPn9kT9ho4KVGz1FIEDUu_pXdIgMaJRhtSDCwxH1_mJmI34U8GpZn3n0Dn97u3re-60Tt6_eRpFy4u3TY0CFe1yW-lzsp2x0dliehk58RI11X98B7Ng1yo3tKRbpHoHmtCt0AXr8V4359qE2mHY8AcPZ9XwA_Pw-RkxlLcQuzyO34aGYY-kGMBwWbchcPRMY7q4i2x490-PWuZHDHfcwDZ2lWZWS5TPp0AuyWR3mO3X2Posol4rqd81EVIQiGYo8rAalo8mTmHJ0PYxtluXVVpLy0)
## Диаграмма последовательности для прецедента "Заказ ремонтной работы"
Исходный код находится в файле `do_order.wsd`
![order sequences diagram](https://www.plantuml.com/plantuml/svg/bPFFYXD148Vl_HH5F7lm9XvaJxw0ry3GIVVAu6pFsjqvwCcT82Yx5xq8WiBY2oJhHeVPE7c5gZVorprhY3WYUqYOxbHzN_t978MeVLoSL6JgelR6-YBO5mlhvbQfyBnqfzhh4pBsM2-g-AHsyMdvojA3XqhfUQmzyIU-uPOt_5CQqe7cLMbTL6fMBvpH_YLD-99ttCePzzoHl4Re5ey8n-TStgIh5Q-vbsQI05KPOk7jgIvzACBSM-iEOL_v2eHh4BOGGvlaXEEQP0d9ZZVo5hVuVUee1wx1lze7jzcYZR6cADrnVUkWUy-oIg7wCYRJUwJzu5LYh92PYysvPlP7Ur-uIpxK074BMtVhiDxNVe_trYWrJ8VkFnvhanuHVv1p4DeyauqqKoTdqcH_cXwtGvCtikHlilm_xZDIlwEexO2ZeLGCgPFbr4tu8-wxeKzfv6AYnZZ0crcYNNAFoEiXbbBIi5cvc3gSzYYbg_ZNw75DD8uVsGPiE-GVr4Rv7mIalFkzTcMhO0dF6umbrGLJdyevbBSf-T_glAGxMXqsUOHll3Q_0000)
## Диаграмма последовательности для прецедента "Посмотреть описание заказа (со стороны рабочего)"
Исходный код находится в файле `description_order.wsd`
![description order sequences diagram](https://www.plantuml.com/plantuml/svg/ZLFDRjD04BxFKup25GxSK0we9rw0QwN8YRV8QhfRrXigE2KDvKSW40z0WJTmgePO3d5VOVQD-7Pja6ErKW-svDsPxsU-yK7k4kjc9rDELJwnsQdBZ1uPcoexojNBcT8JHPGVP_eqiSa9gewIsTGzCzezpzueVlo4A9auOrb-IY4hgVsvxAIKYfESpumzLfPeR6OwJUnh7iYbLBYl1_4wqwav6u5NATqj-Y6rNFivtgjGx1S0BLbgbWr8AZmRMKU8HcbNUuF63rwqe7rc1ju725pXiumOobfZ__TPbH8fxJ8Nchv5heBbMWfqx_mdVn6RqZ6HLKTiNYdR-dpOCoINa5tvENhE8oz0ee1IDk6hmhCRaloI6odz8fo0fx7hbpYCR5tFjLprod4JPYDNzoZsyty91Pgj_yg1AVf21pod34T4ZHj-z7JV3mzPlgFwjnJGzvcRSGA_yij3VKTe0zh706Ww1bAitlgbVozbWrR2mLkf0V071Ezm_ELGzoA_Rp39r36m5n2tzXV4t1TnzzuCkHDR55OtHabDSyLo4nqYmRX6Mocw-rJSHhMtNgtpwAUTOqm7G_CVPHr_dNM8WkW0R_oOVm40)
## Диаграмма последовательности для прецедента "Заверишть заказ"
Исходный код находится в файле `complete_order.wsd`
![complete order sequences diagram](https://www.plantuml.com/plantuml/svg/dLFBRXCn5DtxAwomPi4EiK1TyGDi8qMJZ8EYJkpYcGZ1Aas420fInOeL3uaVIAAcJ1vnVk7wZpYUsvP9DAFGBbgFRwxFupxEqYoosQ2Vo8xfNoGgKorZOsLRgNexKBgZX4ZFU_eYib5VngeR3PBibT7Pwzu79Pyz5oBgPCPA-aKpcfFpdoYdbOnI-SxOSsM5Q9k1ZYFxNZRe6t8MjFH3Fw4bxP2vbFG7mJN-S3R2kqvYqdiD7QkKBaFy94VNViGmT4FNPQ0ZT7_Lr1NuHdTxjj-gu54wwsM1vIldIy3FWBJpK_-nU1otos9-1pxaEDhIvfyG9_tONz8UMYQ8uLVMSMm-B_djwQwvbI6Vl3bs_GCE00HeFCvfZYi_LjOQU__EgbW8hhjy-hAYalA5B9gmXwWDR5r1pmYe2EHGF6C7JKrx5DSLnTrm1N1RIGIvoIC_FSdp7RatWDlY32ni0KnhFsxgms78WVYbrAg6Y99CmlQ1BebFHuwxZnUNuSkF2tHSXr0BSRJWV9ZRYWff45mt0Ymy4AmXQygY70iNAabLfQGD0XCaeSyo77x840WigmKSjWsKwCVTZ1QaR9Jc_lFTL0cbuqUv0IHt4vYtPTxNxH1NFLnNNDmGhCjtGjPIix2u7GJaaB1b1lOMa8DDx4XJbzSJkO4TliDeS3eoZgRp96rveHvKOJIumZttSeFatN_vhbi8u3dGBr12I60sxameKTZii6lb5P-TPdha88ap_1_qaxy0)
## Диаграмма последовательности для прецедента "Добавить пользователя"
Исходный код находится в файле `add_user.wsd`
![add user sequences diagram](https://www.plantuml.com/plantuml/svg/jLN1RjD05BplLwpA5H0IwgK7r1C_m3LIjBMt9QgpBcj724wj8qHHAmo8Ao343xY5j6wQEh_mze-ONJjX7JbLXU3GEdRUcvatyxpPJbAXqz4muY8C-wD4wduYNuoa2YHZoVv07GWjXZoKks8KfKzZbJuRl9RyyIPB0X59_kZX9cCYI6FDwGFzeXcLT4EbEJAPEQJ2P5IPGouIm0y7Yh6TUAH2eL_n3VfC5PrHGUTqJHFRH1DESpoyDgTqYUkvwv_WFjy0XASmq582B80S7KV0-au_7SO4f2N-ccPpoW5UuKkeSXXxKaajKjcFuhs1kXl271yEQrrjZ0EH92zZ7NemtvfM1zFT7ZoNmVuTUqkQcTphKcA8NAHA1wcry2CLSAhWCBw0zXjpOjwuwd2dPVKFYugYYcQ-sHKtOtD4Sp0Uunc-xIcBjPfBkR1VXls1sesR0FYzFNlnYRxIr0816eWbOAPDizGwrii-BKF6t4Rm1qzMS-LRd3w1lO8IsD2OW0kdStC2J1jF0SqPN_ZQKuiEBs_hI-dRdwDiRiLTsALoZfNc_Qqwlg3gmWfe2ElnW38rO-vji8kBhG00quiDS6iJPY9AbtDY1pbIgU1XvcepSsG_cR6Ju5wi2NW1rCoGqunnti7USdshVhkczSuuzfg6pioxnLBq5BOhhFMSmUrhcDui3oeyTxi9mvqrOo8Dz9RcRKrYCjnF7LQrzgK7XTMnhBrQK-a6CMCxXEyKsl-PAGxB6YEZH7ekkBIwdEgsfttwWDnnNQ9bzR3ggNg1ArJSr6Qw1QabCTw6yhoV__7UvDQ6-ut6Ixii9ZSPe964Pwj7Uslu_adMFL_xQEjU1H_56Ulel8SmnQtAiLCtgsyB9-ZgFsRgA_YxLBt1GRZkzwIdV2fd-3R-ZORHRm00)