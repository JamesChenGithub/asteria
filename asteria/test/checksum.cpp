// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#include "utilities.hpp"
#include "../src/simple_script.hpp"
#include "../src/runtime/global_context.hpp"

using namespace Asteria;

int main()
  {
    ::rocket::tinybuf_str cbuf;
    cbuf.set_string(::rocket::sref(
      R"__(
        const s = "abcdefg";
        var h, q;

        // CRC-32
        const crc32_results = [
          0x00000000, 0x312A6AA6, 0x7FD808AF, 0xE643CF1E, 0x0A321D29, 0x601B0C2E, 0xF57CB98C, 0xCEC343C6,
          0x2F0CB3EB, 0x9172ABF9, 0x35F9C1EF, 0x9CA74BF6, 0x668A8270, 0x6B210FB2, 0x6710F04C, 0x6102348A,
          0x7BFD59A7, 0x943D6D08, 0xDD3C3281, 0xE6161985, 0xD3698066, 0x673F04EA, 0x88EB3104, 0x7DAAF2A7,
          0x48BEC022, 0x89B79A00, 0xBF617236, 0x5D305635, 0x89E06440, 0x5EC16CFD, 0xB4124764, 0xD4BE25AB,
          0x2526E10C, 0xF2FF4D5D, 0x26E5E2C3, 0xF23EED74, 0xB1A94E09, 0x49199071, 0xEDBF453E, 0x20612956,
          0x55EC1316, 0xA1916629, 0xAC138A6E, 0x7575214F, 0x224A86B4, 0x3581D18D, 0x4AFABFAF, 0x9D789824,
          0x7D657170, 0xD5BBE495, 0x77921A07, 0x0BEE9980, 0xC3B03960, 0xEDD639DA, 0x3F4C73D4, 0xD65B6F20,
          0x4BC9F62A, 0x313CA3E6, 0xE2945088, 0xDEADCEA7, 0xD6F86D0F, 0x0873FB12, 0xC5F8BC6B, 0xEC44A41F,
          0x13EBD570, 0x821939AE, 0x2F6B1FB3, 0xC48476E1, 0xF4CF46DA, 0x85D92126, 0x0FD5EBB2, 0xE3353F11,
          0xA8A49184, 0x9631691D, 0x1CB2E674, 0x99D8D552, 0xBE5E8512, 0xF5982A29, 0x9DF6BAFD, 0x078C9D28,
          0x85417DEA, 0x9E52BA10, 0xF2E9CC47, 0xDF07841C, 0xD862BF0D, 0xBB731F9D, 0x39B49E90, 0x91EA7256,
          0x505D435E, 0xC0828456, 0x4965ED11, 0xED971A0A, 0x702476F0, 0xD75197FB, 0xE9C04525, 0xB158012B,
          0x9A617990, 0x84601FAE, 0x2F3724FA, 0x864993EF, 0xC2E10B6A, 0xBDDB412C, 0xEC0E3888, 0x41630B12,
          0x56962547, 0x57C7371A, 0xE6149DE3, 0xC4EEFC17, 0x9FC8116B, 0x4C57F16F, 0xC9EB6848, 0xF6288BCD,
          0xBA2B5D48, 0x3200FA7A, 0x9719EF96, 0x1747AC19, 0x8AAF8951, 0xFDA493AD, 0x7D0F4BC9, 0x1635A5C1,
          0x0E224171, 0xE4EF63A7, 0xCEDF7CD3, 0x4AD6CF79, 0x5A78619F, 0x8610F444, 0xA7BF1EA6, 0x6EA65160,
        ];
        h = std.checksum.crc32_new();
        for(each k, v : crc32_results) {
          // split
          for(var i = 0; i < k; ++i) {
            h.update(s);
          }
          assert h.finish() == v;
          // simple
          assert std.checksum.crc32(s * k) == v;
        }
        h = std.checksum.crc32_new();
        h.update("hello");
        q = h;
        h.update("1");
        assert h.finish() == 0x8731D904;
        q.update("2");
        assert q.finish() == 0x1E3888BE;

        assert std.checksum.crc32_file((__file>>3)+"txt") == 3626666760;

        // FNV1a-32
        const fnv1a32_results = [
          0x811C9DC5, 0x2A9EB737, 0x7EA29A85, 0x1831BDF7, 0x52A4B745, 0xFBB9B7B7, 0x62CA1805, 0xA783CA77,
          0x7B14F8C5, 0xB8D3F037, 0xFA4D7D85, 0x21524EF7, 0x1EAEE245, 0xF825E0B7, 0x5C924B05, 0x7021CB77,
          0x4B5BF3C5, 0xC7A00937, 0x22660085, 0xBF6EBFF7, 0xE22DAD45, 0x9D6AE9B7, 0x337E1E05, 0xF82DAC77,
          0xA8DD8EC5, 0x80670237, 0x7BF82385, 0xB54B10F7, 0x034D1845, 0xE8ACD2B7, 0x09D99105, 0x302B6D77,
          0xD505C9C5, 0xD80CDB37, 0x128FE685, 0xA52B41F7, 0x0AB92345, 0xAA8F9BB7, 0x6070A405, 0xB01F0E77,
          0x4BC0A4C5, 0x1EF59437, 0xA8394985, 0x20D352F7, 0x539DCE45, 0x173744B7, 0x468F5705, 0xC78C8F77,
          0x737A1FC5, 0x91052D37, 0xE5804C85, 0xB98743F7, 0xBBA71945, 0x5647CDB7, 0x8A01AA05, 0x8D77F077,
          0x4D1E3AC5, 0xE59FA637, 0x8970EF85, 0x100B14F7, 0x53010445, 0x12E536B7, 0xE7139D05, 0xF0653177,
          0x2418F5C5, 0xDFA8FF37, 0x99973285, 0xE4A2C5F7, 0x0C578F45, 0x0BB37FB7, 0x38913005, 0xC6585277,
          0x3E5650C5, 0xDD853837, 0x91FF1585, 0x271256F7, 0x6CD6BA45, 0xA2D6A8B7, 0xA7C66305, 0xDCD55377,
          0x8C424BC5, 0x69185137, 0x95349885, 0x069DC7F7, 0x3C2A8545, 0x6DF2B1B7, 0xDC7F3605, 0x08E03477,
          0x58C8E6C5, 0xC7C64A37, 0x9C43BB85, 0x020918F7, 0x347EF045, 0xC62B9AB7, 0x2D07A905, 0x36FCF577,
          0xF95621C5, 0x8A732337, 0xA6B87E85, 0xF79849F7, 0xB27FFB45, 0x582563B7, 0xCE2BBC05, 0x7B2F9677,
          0x7DD5FCC5, 0x1D82DC37, 0xEA9EE185, 0x350F5AF7, 0x6559A645, 0xB4040CB7, 0x03376F05, 0x20FC1777,
          0x60B477C5, 0x58D97537, 0x0482E485, 0x87B24BF7, 0xFEB7F145, 0xDD6B95B7, 0x4DF6C205, 0xBB667877,
          0x36DD92C5, 0x0FDAEE37, 0x27708785, 0x4C451CF7, 0xE2C6DC45, 0xDB7FFEB7, 0x9EB5B505, 0x34F2B977,
        ];
        h = std.checksum.fnv1a32_new();
        for(each k, v : fnv1a32_results) {
          // split
          for(var i = 0; i < k; ++i) {
            h.update(s);
          }
          assert h.finish() == v;
          // simple
          assert std.checksum.fnv1a32(s * k) == v;
        }
        h = std.checksum.fnv1a32_new();
        h.update("hello");
        q = h;
        h.update("1");
        assert h.finish() == 0xF193366E;
        q.update("2");
        assert q.finish() == 0xF09334DB;

        assert std.checksum.fnv1a32_file((__file>>3)+"txt") == 3790343712;

        // MD5
        const md5_results = [
          "D41D8CD98F00B204E9800998ECF8427E", "7AC66C0F148DE9519B8BD264312C4D64",
          "B7B68FCE5078A4C8EEC0362E78AB9E18", "24D1FB65E396E77C6A95889B02EDCDEA",
          "95CA519E244290C647712C781060980F", "68BCCF1894D70B00D1CC8C9AFA9006D2",
          "DDEA00049329198EDCA6AE3113B06169", "06D33DEEECCFC210B42DF1260D0E1F41",
          "34193810151967289007E1A8A41CF7D9", "08B839B0917E4C4E40979AD470033E22",
          "01BEC5F107817E3B66C25CF215BAF72F", "1D2F26342F9F5A2524DBAE079238DC52",
          "FEEBE5881FA2F3B2E55C9A3F1B3FC547", "B74038C10EAE24E415324208D580341F",
          "A182D1F3DBBB2EEF2C9CA0557FEB702D", "CF9125057FA59BA5BCB6ED313BBA97F4",
          "939BA051CAFE7278F16FA26D5181454F", "1319CE4ABAEEB156D4C89F606C4323A4",
          "60E2AFE19AA07E4273C55386262EBE31", "A29ECA25AF22203B6AFB40A30B2CF1AB",
          "4BA3B190ADC6B0BCE2E0D9B1F451534D", "22BCDEEBA92A0FF7155DB6455F6702A0",
          "1219C498354B3E18D38373E580A064BC", "75C88CC2F1233516CB41CD885A473D7F",
          "22876FD8FD4502F7A54CB933D170D76F", "0876D8D0121E4554C93A30C18FBBC7D7",
          "8D38716E9EDD604628059EAC77D704EF", "0425B432E7C7FBFFCF23F0D3CEFE072A",
          "956840825DC2CAED7815B9F90C042BC9", "BDCAB46D0EAFB59DA35A3692A57023B9",
          "1DBC0A399323C629D4036EE5E5ED2079", "076387CBF6C90969A4D8055669EFBF74",
          "B8A869DB5A43FD48C6B49B843B855EE7", "A2808B3C8D7BF9891D4FBC825BA356A8",
          "41B72604E1A00FC0F261983596BCD341", "C48DA296AB979BA5242E9929E90625E7",
          "AFA8CA6381C644A686DBE7FCF6057D60", "23B7F2A2BE894FF35760A0AFFB47B322",
          "CE3171B16A391374F4D5CCAA8D5C4519", "02A1C3F3C7BC1A1E8A8623113759F3B5",
          "0C8988C2D46231A09CBE5907981EA6E0", "7300E2BE0454DF4E19D49E1EB4181F45",
          "86E97D2F9A6AFDD3EEAF7DB6E61EDA32", "28277EA78C184091C1CAFEEB745E8DE8",
          "18E9B46F9586FBA8FEE641BF8BECBF17", "EA3397962BF8CCE4329E78C49C43DBED",
          "B1AFB50796ABE7189AD87FB14683C3AD", "C6FF0A9D5B635C305CF89526449CDAAE",
          "04B07B3E42D73A830A0F5B651F894C56", "126146FCD8CC23574B66508EB30858E4",
          "369E6FBDE2304111C1A4D28EF00658FD", "953431548C4069F1A1D3420469448252",
          "482BB820FD904300E6FD90963873DB50", "538CAB982B3151470BF47158E986DFFB",
          "94247FBA1525017AC6DEFF922A971BFB", "E3DCF7465533ED9DD772F304CB68A343",
          "90196C6C2955356859A7A9E7A890F20F", "67C92F044A18D900120180D5EFECC97C",
          "B00D309D890BEFA9DB08056A86C59D11", "8A29CC97B19238C5A91AA311434D5EA5",
          "F8896245D4167019C0D68C67CC6A0C83", "BA1B303E7ACF0D374908FCD1BA77D42C",
          "05E0B6D77C1CAC6E2A77E7A6CCEF986F", "082AC63B636E0DECB9D2040CBC22E1DC",
          "E92D20F7DD4B31FE01069510B40C0AF9", "EDF8E99ABCF7AD1921F18A8FC720277C",
          "879BA77B1810B537126C35095D6B25D3", "EA558E99FBA6EBF976B50509E2EAC5E2",
          "BF94961FB6AB1DF88B1A7EBE79921DC7", "58EBEBEF031F708829E4A23776A6E4A2",
          "86DD4C7876F51662CC047423DB445615", "820FEB1E73E0DD5FCBD8D5454529416C",
          "1512B3E8AA41F80FF0736FA4BC4C7C13", "7F65711DBD69752768F72A86CEFC6374",
          "155481B209E4661C883C3D2A99FEBB3A", "7952B7C98C6CBB451D9D06392D2C4EEC",
          "1633CBA5D9DC7251B0D1FDDAD5818646", "1C20BFBFF4822E4D426B00F0815100E7",
          "861F76986529C7DAE775D10C252CFA75", "D76A6A3A01117E9A0C2479E4D14902C0",
          "AAE276021802E064AE9F02791A00D647", "946EC6891FD451CDDE92FFFEB05E9B6E",
          "65CF1198DF4BA541814F958A0A27FAC6", "94B7A2817B3AF64BE74B9884C0CD81AF",
          "BBA094483232A5359E085F4E565E2014", "8552DA0EABCFC17447E8A24A72B4BB83",
          "CD486256574D514FA4292D43F5F10FA3", "567A8D2E4D03F46A7B1A5DA4BA90C28F",
          "577B66E00A937304A0954A26899C6F5C", "C3C6290F7E8E9782515B73D96E7E0E77",
          "B9608161277649A510AF3EE09A8DD3F0", "5438DBD340E1F9933F66AEA78817B51D",
          "B36B00F9C030627478BF88B8A094D221", "D9DE65F433BBA6B05EDC6E153F2C93CD",
          "F1CD21709245D40B79D07038140E85D5", "B47B7EAC82D208B433C3A20CC146A92F",
          "A2550BCD15C5D75086EBE49CF00E76A6", "38BDE99755CB939636738C6EB288C968",
          "8D927DD9233373889F4D550AE3AF1DD8", "07A2274DAD6E0C1D7775FA7562E8736F",
          "13D999FE3624A381EB8E3B9BA9A15811", "2126346CC4B8E8E8C68D9A98188F6678",
          "A3E41776EE8B5FD3B48699668C23C275", "5D25C1387B32690B0AC40E9321D1D22D",
          "52157E2422A8E8F2A0BAD2CFE2988AF7", "A94B1AC971879DC41467D3D6689011FE",
          "8D9F613C93E0B2178AE92C50CF284995", "57795BCF9E5B413D026A5D0DDAB165D1",
          "60E2F2414A6F077BAF22D441B676E23C", "7C82C6366FE41021FBF9FDECBB063D12",
          "A891E066EE85C9669084A8923F35A5B3", "C81F33FB748B069B645A760B8791D0DE",
          "DA43E225C1137DB1C4B234D5807BDDAF", "D39E3F40205644B0B0F69F3AA822E7B3",
          "345845937DC2427CBD8D747D23991C33", "FE25465B3A6CF53DF6AE4CE639D3C65B",
          "B621A8719AD46B056B03A00409F3B011", "64D73A64A1823810090029C445020C95",
          "63C0FAD58AF870D87FE6BB61E61F1ED2", "6061D93284C1516A6C99E667ED00755B",
          "8CD81F0F4536C18477DED17610840EE5", "F0F7CC1FEC0DC900B81676B432BF3BBF",
          "9F30C26BE78BBFBB3BF777A89F9BB4F8", "65C1BA86506E577A847AD6FC585DC01B",
          "8341C2174A953D048FEF4A92A38041C3", "B168C6C4896F029B2C7C5990C94E7AC8",
          "99AF26FBD01C1F26AF0D2C80855D4273", "60F727F61ACF60E7314C16E0ED9805AE",
        ];
        h = std.checksum.md5_new();
        for(each k, v : md5_results) {
          // split
          for(var i = 0; i < k; ++i) {
            h.update(s);
          }
          assert h.finish() == v;
          // simple
          assert std.checksum.md5(s * k) == v;
        }
        h = std.checksum.md5_new();
        h.update("hello");
        q = h;
        h.update("1");
        assert h.finish() == "203AD5FFA1D7C650AD681FDFF3965CD2";
        q.update("2");
        assert q.finish() == "6E809CBDA0732AC4845916A59016F954";

        assert std.checksum.md5_file((__file>>3)+"txt") == "67C62663B722611BA87041EB05870EB9";

        // SHA-1
        const sha1_results = [
          "DA39A3EE5E6B4B0D3255BFEF95601890AFD80709", "2FB5E13419FC89246865E7A324F476EC624E8740",
          "9BBC2BB3533171D8E501F28D8BC075051DAF6D60", "666DF4C2B88316FC3580B6131EFB2519FD839F5A",
          "12EC1179A61868E15D307D9487018947724F3030", "88C70F7B77F2DEE9F3878B11205196074D7F063E",
          "3F84309612F276D8B9005EA969A56D8FB585A09C", "455ACAF77FDF07461E3412481416CCD3DD2772E0",
          "15F1B9863855123BB3F7D26739E5B140774ABC26", "F210A1C82323C7783B639BB63E42B1D57D5DEAE4",
          "17326AC495033B6D24F75AFF0DDB90C5F2FA22FE", "175B3B8424FAB42F9E42E1D23970692FB182E7AA",
          "209FEA0B5BC787CA3C5FE4BEE2E43A7A659F52C1", "8A37BEB17AE39A67433D826A4A35C91532D8C695",
          "AC4F90A5C535D171F3BC45FD5CD8D9DA7C70D7FA", "277104DD7FF67D71B3B938AE44083E560293CC48",
          "F0E138B258BC49C9460EE6234FC521FAD4B0FC7E", "057124F61B03702D1536F61992C658B8CD52820F",
          "EF24DCFBCFAF276B43E8028B3B99DD95277157AE", "960BE836586A16F17A67212C0018534FE1D97147",
          "613435029C90462BEED9FFC40FDD08CF1146895E", "CEF97E7DB40FFD5C6FFCD62B4CFB82301D100291",
          "513AEBEF107CE2CB071E989C73F7D3017F9DC03A", "E7CC18EAB37538F0D6A546FA86FA7010A61A1AD1",
          "CE5A222F5BD7DDCECBB738857E6951D15978FC00", "295047C57492895C6B682A617F2012A4FA84BAAE",
          "35BE880243ED8E2489BD252774E887F47963ED60", "F64C4595DD2C86E59D50779854E0A61168B52442",
          "94E7F3CAF7C8DA5326837D693AC3F82AB1E40CBA", "25FCEABCB718D7FE54729CF5BD2A1255E5C541ED",
          "C1E7943D42F9D8D988EE7EC6EDF79EE1F35AD2FA", "3862C0C71BABE9599E96EF8426007597605B9329",
          "123679E35CA60EC361E454E53A00458EF269348A", "E6D7D44EF3CFC912B92DE50AFA71819B3395A44A",
          "3EA3F92C5D46A251609820D92BAE0AD883A0BB01", "BD3ADB6E817ACF6429D5D5329192C04F82A949D6",
          "A478C13CC918E173AB8007D7D23D6658D8F27054", "3514CFE30FB1CD41D5D5A70DB38970B6715F20B4",
          "8DDA62B92DFF7B0754BA340DBD87F906B8979A7C", "10EBCD0091E0EA0CF5D122418DE4957C47077DB0",
          "EEDC83DA2CCD7273353B91F85FDCEC42871F4798", "865F91DD1CC2CFC6E8D086C4A8B9F41C43173636",
          "04D2625191F6EA8402EDB4F1EC80713DD0BFD13C", "5349062A821F3250BC6161846C189C1BFC9E88BC",
          "BC09461492B7F31DDFEB4EE6E8BCCCA95480C280", "5C6AD6049FCCA0CAB4C1BD4870396B10ACC9193E",
          "B9425D27355017EE2743C725B948D8CC0E01ECFF", "82CD91878488A958488066791797D0E58C70F733",
          "81A136423B76735A00C1AC46D1A26F5F26A59D81", "5677B6FE3C4BF5E788D5BBAEDD62ACA002684CF7",
          "117730BC6D68C4D1AC1511CADF1C362E7202CFDF", "7D2A7DA5CFFA00FC11C0203ABA8597E95BE7EA8E",
          "6B607DB3C2F9A5052523D09D961B77AF37608674", "CA5553CF0370DBCFC1C64E45EEE463DA3BE2713D",
          "17F3D274211973B5D86047F490E3CD46D7E6766A", "D426E6CAE38F71BE0BAF5A59EBC7DC88DE37F516",
          "126A0B5F20F9C86D07F717E25B5C4D1663452E35", "C409F58CA48CF52A78BF2B28E027B6F3C697B9BC",
          "40E6B21D8A301BB35C1673D2698A625D2DC6ACF6", "677AD880118F490E072825211ACD66EC035F06C0",
          "A3BE7C3091A687AC1BF8F49582FF1B09B7E54DD6", "4F44298543C013E8CAE33B39F5EF59A5A921960A",
          "E59C691E55331AAD61DBAB99816C22A35BE1C07B", "AC51952B98A011FB3186AEBF09CC9394BCEB3326",
          "106BD904C28D5D1E222D5C9DB45A281313194ED3", "FF62610CFDA5BFDDCF9A8BE1007C8DC813FC07A1",
          "D47201383086A617FD13C18FFA243399D2D81068", "A555B5CF32C951F40A7ABDB52C1071D4A2F9FC61",
          "708492E7F6129DC474C032C7161316B7C78F5E52", "463B73616B3A4AE1DFCF8D1E540B383813C92E6B",
          "CDBD4D2E93A542D507ED4C186F0B7552375D8B21", "47E091CBEDC401FFC47B573B64BDF272F4D5FDB3",
          "AD57CF58AA0EAC0D7784D2BF373DACA62E24381D", "A20EC52098A20B34EA5854AD61377BA5AE409EA1",
          "A1AC6B4E8C6DC3474756705D2ED7B416138D61E5", "EC8F16B7AE3DC6A8FC35E38B3D22AF1E3AA37CD3",
          "3996734E86F987C4279E3B08FE8FF406836FFE8A", "9840310718770574C55F8728DBAD6004DD61E82D",
          "2E404B3C74A8E7D1A19011C7D9326171960C983D", "FAE2FD285EDB3C5C7F1AC2F6BF6C85DECF946EB3",
          "EC27F0308AC0B713044A28A0A0C60F584BAEFB44", "52D0AF39F2E24BCC4CE481DB5761135A7CD37D0B",
          "6555051B96164B616E59FEB2C1B0AC110473BBDB", "1A6383B4A621844BA3C1495C814B506C729762A5",
          "55CA912D322310D27CF340534CBFAC9E3ECE77E9", "53C31F48F83DE8F65B9C8E465D95B1C23C1AD4F4",
          "0ECF72BDDB5AB58364BB88D353F7FA0C5D631324", "F0782507E5CB935EE4899D25E3A5E281F74FD65D",
          "D0BE894838A1EA700AAD99F18F3DB84AE01833F5", "DD2940C36F0C7798D5EFD8DDD4ABE46C9FAA874B",
          "C0A613A5A9CC8D7A693E078DA2A967800DFABB5F", "B469D611D3403A9E12B18C62167A67AC088CB588",
          "36B749BE6E38211AF3A2EB832639EA62ECC405C3", "08E122730946DD3A7EC552792180C222E14FE54A",
          "F7A592DF06F136A44A87FF5FFFA71719C3E7F90B", "DE953ABDF424B10188B0115C5D654AC86D90EC9C",
          "7E0FD84A04A640AAF441BABF4D115A2605C5FFA1", "30BFD07640052084EA9AAE9DD69F22A8488D0736",
          "170E187CB6B0DF88DF6284DA6B15B0D4BAD42F09", "977AABFCFDB977F7F2A51D29F9B956F99C3C885E",
          "BFD4876C1E3D5B9976A11BCE9A246C4B69CC4618", "4B561180D1BA60F05A631F96F714325A1FEDB347",
          "122D1EAC5F7A126762A8B51D182011AEDFC32CF3", "9FD03B59A41313FC8E2800AD5AAA299749FD008B",
          "7148F202DDA9960688FF8362E22E78ED9379A6AB", "FB95B409D10FDCE3A4AD16E35EC111FBD3EC753E",
          "DC4144B9DC2662231ED7F89EF9D779D03287D458", "9A329E67AD3975AD28E9B374F9D0F699D3A06C5C",
          "DBCBC8461BA93C4C09A742DC1ACAE1BD1BE80099", "A4366A7AB5838C8A55B88DFBD0DA85D71C8DACAD",
          "51005855312E5585294D2BF43E4F14F7DAA17448", "D347F7CD04198ADC63293CC2AC9C7D08DC686A2C",
          "532DD2328A305F0C809B11B666ED02C5DB2C48DF", "BD3FA95D48F6A0862264431BDE46092ED826135A",
          "90DFFC3F1BCFB76DF502B739AABB8C72B0CF009F", "9E6DC9FAE92EF51E85071A0B3336EA4494740283",
          "603D7D0D4AB926BE6E7699E09D5BF9BCDBBB394D", "51C1ABD5DFD13EA7D671B8EFE0B318D23AA16D74",
          "299F577E14B90351DB885D1F16935C2B92D8136B", "3ADD065C558B7B9BC04D73673429436602D4A17F",
          "22614330B65EDE754F652BCEE0FE59E387E960EF", "8B380F11F875B18EB1BD0B39A8D60F752B2E57A3",
          "1E0EBE55E292F7F20F1DB6426D88A2EA3DCB2D5C", "12740FBAB42264E61B17F3C234ACF1AE9DFAD7BE",
          "C2D328C68C0863EA596B4C46361C8A1321A98D0E", "53DBD67B08BAABD0FAADFD505CB54B09A9D8A3CA",
          "338748A8A6C46B4A9B25CA09775F4137374F17AB", "3D22D695ED0EC9CF888A9D25644EE95A830FB94D",
        ];
        h = std.checksum.sha1_new();
        for(each k, v : sha1_results) {
          // split
          for(var i = 0; i < k; ++i) {
            h.update(s);
          }
          assert h.finish() == v;
          // simple
          assert std.checksum.sha1(s * k) == v;
        }
        h = std.checksum.sha1_new();
        h.update("hello");
        q = h;
        h.update("1");
        assert h.finish() == "88FDD585121A4CCB3D1540527AEE53A77C77ABB8";
        q.update("2");
        assert q.finish() == "0F1DEFD5135596709273B3A1A07E466EA2BF4FFF";

        assert std.checksum.sha1_file((__file>>3)+"txt") == "6BD103FB2F8F84E6A7B36D27E1FD6243B6320BE8";

        // SHA-256
        const sha256_results = [
          "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855",
          "7D1A54127B222502F5B79B5FB0803061152A44F92B37E23C6527BAF665D4DA9A",
          "900EAC36EE15DB25D52B8066FE8278FF2ECFC573530F1D2C9B724B3077900C3E",
          "75A73050545F2DB3BD57976D4E7A616FC6A1E0A3BAA3905531FA4C124ECF2E6B",
          "05D0A8B2C9522A6F5340D9D975B61FED153656B6802067D392B2064FB81CA4E0",
          "3FC078E782AA8CA0DC7E2816934A16FB2C42F6E30AC30BA341FB1145CC557AFD",
          "1B2A2D8279D810ABE6ED6D669967798358CC15C0A3FDC5A43AB54F082D892CB7",
          "36C5AAD1C57AF017D3D516E550FD949EFAA08BCC658477D817A94C27FB8B6142",
          "2C5E9855C334F91FB7E058C692E4F170688BDA08446C22709989F01918AED323",
          "0CEA5CBFE2751C43C4FC33C19D51E19AF33D134DA6EA4C7B574DC7EA85C60B7E",
          "583AEDD211A41DA04411420371A3A4FF82A60ED61D683B881900CE21686B7269",
          "5CE757614430077D72004699CB365272999D3BF3ED9A9A55E204A604CD0DAF9A",
          "A21EBE50B16464003C077E086BC8CD1003455EA3585D60207C72AED9C74A2A6C",
          "1476037AD25F9834C460F444C213AAB402BFC4D3030A1633049C5C88CD7B3BB7",
          "11128A0B9404EB9079A0DB7B532FB622EDC8252ECC1A7DFB6550F061A1BFDF93",
          "E32D647F12A47694D6CEFC7C6C78C610C648DF293B0752D72251DD0E3338E69A",
          "33B2BB33C10BC5EEA0BC7C3CC48CF74504B3C1819FC50F82B08CA545A868E5A0",
          "6E7E0AB5669D28169F129F046B41DF9CBA881393A13D99E540AAB3FC96E25884",
          "DFD6C6BB4794BE8AEC24F9FB94FBFE21FBCD2C1E8541A7034B00A3FA7074AC6E",
          "B27FF73FD5B285B8DC07010868ADCCDE3B265C8ABD57AB659692623DA2235266",
          "478602C5DCCBFC1A50B8C23AD375B588BEC4AD4E9C05AF380339F0AD2AE9E5AF",
          "9BA401F6E767C64A0CFAFCB1557AC8838B40C54DCB48E8E81B418C95FA0903D0",
          "C73D85008C95DCA71476071974251A6B3E89A769BB14B1A85C4DF3BE6ABE5DED",
          "6B53F4D1B0B189E873661CFC309FAED68A8BC7D64432542AB3F5DC39FF24FBAD",
          "EA396D3B30DDA46C7765F80A4D95A96F3BF495C5E2D1B6A525F0DB8C99A49BF1",
          "4E8B7471654C6596872F506F8067EA9EEB77DE2495D1DDFEB6AC5BC59F031477",
          "9EE9582B5C6D792142000F621F2043686FE4716E58178ED8DD3B2626B76A4EB9",
          "7F4882497A496D4E96F00D1E97E18148E24A822394BD2FE216FC39B38B16C8B6",
          "1F8B26DD005083F4A87964508874D0612F5C952FAF3FF80F5312A95BA10FE2DB",
          "F347E95C200BF2D994CDBD051AA7680506ACB18D845A24A86A1AE43922E9BB90",
          "EF40DFF56E39774797A73D00382F31388A3E386D45F7545A624F9D75D1EB7A35",
          "05258895CBEFB5B081E6571CDA5C1E47BA6F70A51AA4C384679BA7C6BC89D158",
          "88DC008805F2D63DD54FFA3318CDEC4067E4C1C0625FD9E51FB04EBA8D84F596",
          "C426E780A387169E9D8F36FABA70792A4C8DDDC877CD9EDD43459DDBFDDFEDC7",
          "0F942A46447946EBCE01D542DDB5828E030A406E06F127DCCC8FA385A2CB8946",
          "307CEC625220871D103BE634961F0DAF6ECCEA03C13285434A0D6276977A69D8",
          "3D7824C3BFEAD991FFB9809DA04B9055F872CA943FECE6C1B98CA1E6C459D4F8",
          "CA34A347F21285CF72403FC5ACA05ECD2CA37D7C76100F0F5F283251EB3A61BB",
          "8D837498A3087D9C4CF175A270E9D6D9DFB7FDBC0CC713E10B8B98DC45BD12C5",
          "16E7A8FA7EBD2523412EB201F0370146AF9CAA5B880F7C46CCE311EFBDF6F986",
          "78838E1AD1A5FD09D12CE1C9AFA39D6A36A27A4A9D61C3C308BE10B4F8A29616",
          "3CBA195C61DDE8A42F6F4D70F06F620BD9C293D5768C93713DFD9860E8076A4A",
          "BE18F449FE0F72A3F00C8093ACDBA8E93EA262AA43549560C23D68F9D7530531",
          "4371568D8FD47F3287D8B4200E5C1D74D6016BB65E008036B7A7857C9EBC0FF1",
          "EF127EE139547AE18887D3B28F47D5B13D64CAE2259C29519677D47BE0AC6405",
          "C299F9DD68C35C6EDFFD294ACF70288C22773B8B9B61A2EDB37FB127211B6AB8",
          "2C6F0BAA06D55686E2E1BB731BBF08E64457AEA5900BA353127AD5896C82EEDC",
          "5302D878B343C51210443B8F5A262B031F3602CAD13D4AF665D7EDE69915E292",
          "6774C0CC7092FA25BCBE706B82C793B3292E00EE44D0C0C224F0780A3DB4A64F",
          "CDC87CED5AE9279F883A79EA25B05FB4C14A636C0E1D7ED5E70734E423AC6B8F",
          "4CB90E634D27F91B27173A5AC3AD4B76265336A61FECBCDC139779BA4BB63FBF",
          "A9A366010ADAC425E270879FBDB432A52504EFB26CA77BA471D5F0B7FBE3A589",
          "5B3E79546DED00D9CF63E3BBFC532F93ACA9A3829B51F4F83F8FE76020A5100C",
          "0571323B6B62DD3174E3D31BE7426848687992F035903FDE59A57CA219557A9A",
          "1749312208A18AFFB899E7760684502E21E44BFCF3D7BEB7FB967EAC6323E0EB",
          "F5440F6B219B145D90D4D9DDBA010719C8502AC626E3058D651FC1DCFF165ACA",
          "C1D5C74B31B73316664158296C171CB0D9F8DD682E7EE7C6A7B794EF7603247E",
          "21C0A48E3DFD11491249BEB2B39D3B0EC990A47E8A0A0B9344D489D70CD3D187",
          "D9BE36D70072A14AA8030DB9409A9A98FA82D4C9FDC76E20E27CF5F685B7FF1D",
          "EDB06E42095CC487145C73D5ECC389CD8D5C7201C25A44AD05D1A64CD7773118",
          "05A1357E3CE10B220E56B34C695A62B7689F470140CC5D132BCC3CF584E63BEB",
          "028FC45F19F80932CA26A6791FA42B278F3E332EA99B9DAFBC22B1CFE80F6CBA",
          "D31EDEB5E90BE2AAA0D6022907B5C4D55D485B9D75C1E24DAB878CD9C08E80B4",
          "035FB9DFCB5D5A0DD25F2A636340F60E2551A2641D56A18B70489463F72DF924",
          "FE4EC1ECF2BDF33A3E1DBF8C1A8448E3E7576EECEBC51AB22A82557534766955",
          "43C04591C926636E52927068E27C41140EBA352C236152794B52A08F36B64A11",
          "23A086947620588D7C2ACF4C074B32B71F12D45931AAE2C105419956432B5EC6",
          "6E58CD04B87E41D0354CD17FE5E3C2B77F3EE8662217F95240013D3B1E38BDFB",
          "D3E7A2BEA41193779652CFAF6A5B4C26CC380200D92933581BF1D90F95AAA7AD",
          "3B76E19239F010D63E63F10253F384E32A5827300D279991A1C143D00826D44D",
          "22119D4508BAF69F4DED365370438F311ADD7D57E4F9154FF9A30876E7663975",
          "5A9B6A69297B52AAD0E09F0A4870F3A5B264CAF08A81FF6B7B07D4DE6E4ACA7E",
          "98A6C7ABDA55BD7E3088A9F20F2C206F2847C2CE979875B5A829766DEC25F1E5",
          "FAFDBC65BDCF29E8F6033E205840969B3FA02A24139AE4BFC7EF64A238A5427C",
          "96D98E85CEC1BE22700C4817588AFC3B670BAE9BB7A284BD4DC27A3BAA89F480",
          "1222598F08A69AE4341F12CB2B855B17103282B901E890067724FC3211181387",
          "8FB07105D9C4DC0E7F7277B25F12308CC1D194BB665F006BF431963E700642B8",
          "0B6D64A8C5446B4EC3124A11D5BD40C520E4D8FADCDC70837FE9FADE0B7F597C",
          "C1E2FFE00BA13B121383CE8EED1E7FA198DD3DC27359BADD4AF1240717F3CD31",
          "9ADF1090398278568C24C0A0F86C694F7400C75B0C2A5F6A8D00171B2EB62BC1",
          "E49DE3BBCD069D91ADFF8679E6818F221F2F99FCAE647945B27A648ECB92EE43",
          "F63077AC53E6BAE6858C86A4777D51C23D50BBA0D98E56DA7DFB7EBDCEEEC5D2",
          "B2FB87AB63AFADE6ED35E55AED38E99DE4382E67485B54E8FBDEB9E52822F000",
          "7ED855235ABB33E15C5AE1B936FDD394C79F585A4ED1E11B482D5C0B97EB55CB",
          "A59C62399E294AFD9389950C8D610E8E5C27EE51284C03EB5DFBB75E16884A11",
          "3B53402260FBE0C0C2C96FB9A60EAF0696290D1B6A7E7C4A0B91890839908B03",
          "87439B9933F176F159B5E89AF5F0A676A165409A68FA63224EF56F9332113FEB",
          "DB141AF3F8AA5A1CE67F1D789AA5CA7A34104E94139A34EA92593BA62AB365D6",
          "FC8FB0892AB89DB5D8ADE46B2084FA3E55F764357EEEA0308C040D82EFA95C58",
          "47AA8CEAF6A06DF628B2275B4E7C3426E7CE1C17F9339AFA694113A8A319F5AD",
          "16EB24B9A4B8EBC9744B6F0BF2C2BCA1FF3175BD9B619A23E499E95BDFE9CA02",
          "BFDA054EFDEB50BE3B217B01C8889A2737F6AB44A03A106A79CED0B88A9FDCB9",
          "795F99E47E8FB588355B8EA537807DD91CF481AFCD0AFD220C35BB7E3B7A7B18",
          "5341667364F180F82F3BA153DC25F59D8C38611A1D9505FA3B0D81A6276D3F59",
          "B474F891E69EDFAFA5A8B776CDD4CAC7A491C1A0C13197F5FBF85AE4160115BB",
          "49FBC7D4E30F1FE11891DCF998F870010C468C0A7D4968BF9AB0E1A16A279BF0",
          "287F867A10797710C789A65BC4044B39AC05B75CBF4168FAE9AE5FA55A4FFE50",
          "50EE84CA77ABFDF8780543A8BC2CAAA7456846250C91F652A0815F6BD376098B",
          "F025B7ACB42DF61E4BEEB4946945C2DB1C3039B733F09BDB2A3D6F50F5EE6480",
          "D01965EC1D532B26634A93F5B14E3938EBC838F8C9FC3B64DABDDE955DD25932",
          "6BAFF87C194653E2AF9D174314E81ABE593E354FBE78E9C8B3C95B92CF2059FF",
          "0CE61FDC27857B5D7A331BE55028C5EB568397D874DC8BE191191D2FF8B6EDA2",
          "3674848B6F757754881CC69762F5ADAF039D7CFB0EE00C684CDAF46406F849E4",
          "0D74282E83982E140A7B08FA8728A6A7957FDA125838EA258478D2BAC9E4DCE7",
          "C2801661CDD7C3592C83D1C423AA95790A89738559F125A5EAB617B3C06C219F",
          "F37ADCD9B32F8EB79534E37D3B86FE87BA571569D06BB41BD22A0E43ECB49C60",
          "E3CEDE5D6E2B787E6D0440B2856552B3C754534E8D0A230A819C8B233528BD8A",
          "D238FA0A3ADBF048B272224F5F2B27738060B1085032ADB9296A8BD428966788",
          "8DFF09B509597C9FB7E9ACC1A5D297ADCE18C1BB65A8D63186D363846F833F6C",
          "B0C40EC77145CCCB7ADFAFEBE6963DC4197C3F132FA2D1A2D60064CC5137ED73",
          "E082D08C7E54C0C3FFC7F87B3DD476091C485F2E9106BD9F8693895698385248",
          "E2B1FF05B6CC71E8E6C63C679FB9040DE3E7A4B2CBEC553BD5B3A105CCCD4BD2",
          "09EBD8E510FE4D57437C1CD0541719DE59250235768172C254B3BD1760C33E1C",
          "A14602C568C53A66C2C2022BBC724D4DB6D3D7B554E77A0D9714B8EDF0CADB7C",
          "79547DB658AB9C6E18EF1954AC66271BC4AC301570837FBB58BB73C78526841B",
          "C4F9306A08C89B3D02B0AAD5F30034067F1DB1C509F03AC3D07B923801048F68",
          "8171FFF8997302078DDBE5A3757581995265C04F68FAED098742034170085DE5",
          "8C4973F47D1D0A7B315D1FA031645FC629E809BA74C00FD288F0D9EBFD609E23",
          "ECB0E0FC1D3A0715AF3E708CFF019D517051862B81841D23D867CD6006160CDC",
          "AA71DD0625EA16F0619E672A546ECB29814FC6EDA268020DC3C21E6B8720B3A0",
          "605EA1B5DFBCA577D0624A01E9A9B842C69191CAE1794ACA47E54A4ED6ACF0E1",
          "45864B11E7E2C803B89901EC4F5386714C180ED9036C61945FBDBD2D7FC55ADE",
          "A88FABE4AA404E694A0989A46716DF6EE2E2895A56E898A48253A7FEE2BB56EF",
          "5DC9818474866E2BF08927384A7968F0B53305FD45CF82535AA43FE65F7D51E2",
          "8955764CC5583DA76BF36304BB7D1C61FAFDE3D619C301DDB2E91BEAD98FC09A",
          "CA2BE7BEAE3579FA2C951F03E03887503057DE8496F728D8EA899C6E5531F500",
          "D1E3F06B406DEEC956B84C108140A1C8532304B5BB7498EB744B20C57EDFAB12",
          "5E1094168FB46C75DC57FFF81E032657C217D98B4058BDB773DFAB537AEB0954",
        ];
        h = std.checksum.sha256_new();
        for(each k, v : sha256_results) {
          // split
          for(var i = 0; i < k; ++i) {
            h.update(s);
          }
          assert h.finish() == v;
          // simple
          assert std.checksum.sha256(s * k) == v;
        }
        h = std.checksum.sha256_new();
        h.update("hello");
        q = h;
        h.update("1");
        assert h.finish() == "91E9240F415223982EDC345532630710E94A7F52CD5F48F5EE1AFC555078F0AB";
        q.update("2");
        assert q.finish() == "87298CC2F31FBA73181EA2A9E6EF10DCE21ED95E98BDAC9C4E1504EA16F486E4";

        assert std.checksum.sha256_file((__file>>3)+"txt") == "F5C962601B413CCDA2FC14D64D98479D9FC74C90C2DDE15F25EE9922E57F5074";

      )__"), tinybuf::open_read);

    Simple_Script code(cbuf, ::rocket::sref(__FILE__));
    Global_Context global;
    code.execute(global);
  }
