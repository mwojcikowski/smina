#include "builtinscoring.h"


namespace smina_atom_type
{
//vinardo scoring has its own atom parameters
const info vinardo_data[NumTypes] = { //el, ad, xs
    {Hydrogen, EL_TYPE_H, AD_TYPE_H, XS_TYPE_SIZE,"Hydrogen",
        "H",  1.000000, 0.020000, 0.000510, 0.000000, 0.370000, 0.000000, false,  false,  false,  false},
    {PolarHydrogen, EL_TYPE_H, AD_TYPE_HD, XS_TYPE_SIZE,"PolarHydrogen",
        "HD", 1.000000, 0.020000, 0.000510, 0.000000, 0.370000, 0.000000, false,  false,  false,  false},
    {AliphaticCarbonXSHydrophobe, EL_TYPE_C, AD_TYPE_C, XS_TYPE_C_H,"AliphaticCarbonXSHydrophobe",
        "C",  2.000000, 0.150000, -0.001430,  33.510300,  0.770000, 2.000000, true, false,  false,  false},
    {AliphaticCarbonXSNonHydrophobe, EL_TYPE_C, AD_TYPE_C, XS_TYPE_C_P,"AliphaticCarbonXSNonHydrophobe",
        "C",  2.000000, 0.150000, -0.001430,  33.510300,  0.770000, 2.000000, false,  false,  false,  false},
    {AromaticCarbonXSHydrophobe, EL_TYPE_C, AD_TYPE_A, XS_TYPE_C_H,"AromaticCarbonXSHydrophobe",
        "A",  2.000000, 0.150000, -0.000520,  33.510300,  0.770000, 1.900000, true, false,  false,  false},
    {AromaticCarbonXSNonHydrophobe, EL_TYPE_C, AD_TYPE_A, XS_TYPE_C_P,"AromaticCarbonXSNonHydrophobe",
        "A",  2.000000, 0.150000, -0.000520,  33.510300,  0.770000, 1.900000, true,  false,  false,  false},
    {Nitrogen, EL_TYPE_N, AD_TYPE_N, XS_TYPE_N_P,"Nitrogen",
        "N",  1.750000, 0.160000, -0.001620,  22.449300,  0.750000, 1.700000, false,  false,  false,  true},
    {NitrogenXSDonor, EL_TYPE_N, AD_TYPE_N, XS_TYPE_N_D,"NitrogenXSDonor",
        "N",  1.750000, 0.160000, -0.001620,  22.449300,  0.750000, 1.700000, false,  true, false,  true},
    {NitrogenXSDonorAcceptor, EL_TYPE_N, AD_TYPE_NA, XS_TYPE_N_DA,"NitrogenXSDonorAcceptor",
        "NA", 1.750000, 0.160000, -0.001620,  22.449300,  0.750000, 1.700000, false,  true, true, true},
    {NitrogenXSAcceptor, EL_TYPE_N, AD_TYPE_NA, XS_TYPE_N_A,"NitrogenXSAcceptor",
        "NA", 1.750000, 0.160000, -0.001620,  22.449300,  0.750000, 1.700000, false,  false,  true, true},
    {Oxygen, EL_TYPE_O, AD_TYPE_O, XS_TYPE_O_P,"Oxygen",
        "O",  1.600000, 0.200000, -0.002510,  17.157300,  0.730000, 1.600000, false,  false,  false,  true},
    {OxygenXSDonor, EL_TYPE_O, AD_TYPE_O, XS_TYPE_O_D,"OxygenXSDonor",
        "O",  1.600000, 0.200000, -0.002510,  17.157300,  0.730000, 1.600000, false,  true, false,  true},
    {OxygenXSDonorAcceptor, EL_TYPE_O, AD_TYPE_OA, XS_TYPE_O_DA,"OxygenXSDonorAcceptor",
        "OA", 1.600000, 0.200000, -0.002510,  17.157300,  0.730000, 1.600000, false,  true, true, true},
    {OxygenXSAcceptor, EL_TYPE_O, AD_TYPE_OA, XS_TYPE_O_A,"OxygenXSAcceptor",
        "OA", 1.600000, 0.200000, -0.002510,  17.157300,  0.730000, 1.600000, false,  false,  true, true},
    {Sulfur, EL_TYPE_S, AD_TYPE_S, XS_TYPE_S_P,"Sulfur",
        "S",  2.000000, 0.200000, -0.002140,  33.510300,  1.020000, 2.000000, false,  false,  false,  true},
    {SulfurAcceptor, EL_TYPE_S, AD_TYPE_SA, XS_TYPE_S_P,"SulfurAcceptor",
        "SA", 2.000000, 0.200000, -0.002140,  33.510300,  1.020000, 2.000000, true,  false,  false,  true},
    {Phosphorus, EL_TYPE_P, AD_TYPE_P, XS_TYPE_P_P,"Phosphorus",
        "P",  2.100000, 0.200000, -0.001100,  38.792400,  1.060000, 2.100000, false,  false,  false,  true},
    {Fluorine, EL_TYPE_F, AD_TYPE_F, XS_TYPE_F_H,"Fluorine",
        "F",  1.545000, 0.080000, -0.001100,  15.448000,  0.710000, 1.500000, true, false,  false,  true},
    {Chlorine, EL_TYPE_Cl, AD_TYPE_Cl, XS_TYPE_Cl_H,"Chlorine",
        "Cl", 2.045000, 0.276000, -0.001100,  35.823500,  0.990000, 1.800000, true, false,  false,  true},
    {Bromine, EL_TYPE_Br, AD_TYPE_Br, XS_TYPE_Br_H,"Bromine",
        "Br", 2.165000, 0.389000, -0.001100,  42.566100,  1.140000, 2.000000, true, false,  false,  true},
    {Iodine, EL_TYPE_I, AD_TYPE_I, XS_TYPE_I_H,"Iodine",
        "I",  2.360000, 0.550000, -0.001100,  55.058500,  1.330000, 2.200000, true, false,  false,  true},
    {Magnesium, EL_TYPE_Met, AD_TYPE_Mg, XS_TYPE_Met_D,"Magnesium",
        "Mg", 0.650000, 0.875000, -0.001100,  1.560000, 1.300000, 1.200000, false,  true, false,  true},
    {Manganese, EL_TYPE_Met, AD_TYPE_Mn, XS_TYPE_Met_D,"Manganese",
        "Mn", 0.650000, 0.875000, -0.001100,  2.140000, 1.390000, 1.200000, false,  true, false,  true},
    {Zinc, EL_TYPE_Met, AD_TYPE_Zn, XS_TYPE_Met_D,"Zinc",
        "Zn", 0.740000, 0.550000, -0.001100,  1.700000, 1.310000, 1.200000, false,  true, false,  true},
    {Calcium, EL_TYPE_Met, AD_TYPE_Ca, XS_TYPE_Met_D,"Calcium",
        "Ca", 0.990000, 0.550000, -0.001100,  2.770000, 1.740000, 1.200000, false,  true, false,  true},
    {Iron, EL_TYPE_Met, AD_TYPE_Fe, XS_TYPE_Met_D,"Iron",
        "Fe", 0.650000, 0.010000, -0.001100,  1.840000, 1.250000, 1.200000, false,  true, false,  true},
    {GenericMetal, EL_TYPE_Met, AD_TYPE_METAL, XS_TYPE_Met_D,"GenericMetal",
        "M",  1.200000, 0.000000, -0.001100,  22.449300,  1.750000, 1.200000, false,  true, false,  true}
};
} //smina_atom_type namespace

builtin_scoring::builtin_scoring()
{
	//set all builtin functions

	add("vina","gauss(o=0,_w=0.5,_c=8)", -0.035579);
	add("vina","gauss(o=3,_w=2,_c=8)", -0.005156);
	add("vina","repulsion(o=0,_c=8)", 0.840245);
	add("vina","hydrophobic(g=0.5,_b=1.5,_c=8)", -0.035069);
	add("vina","non_dir_h_bond(g=-0.7,_b=0,_c=8)", -0.587439);
	add("vina","num_tors_div", 5 * 0.05846 / 0.1 - 1);

	functions["default"] = functions["vina"];
	
	add("vinardo","gauss(o=0,_w=0.8,_c=8)", -0.045);
	add("vinardo","repulsion(o=0,_c=8)", 0.80);
	add("vinardo","hydrophobic(g=0.0,_b=2.5,_c=8)", -0.035);
	add("vinardo","non_dir_h_bond(g=-0.6,_b=0,_c=8)", -0.60);
	add("vinardo","num_tors_div", 5 * 0.02 / 0.1 - 1);
	addparams("vinardo", smina_atom_type::vinardo_data);

	add("dkoes_scoring","vdw(i=4,_j=8,_s=0,_^=100,_c=8)", 0.009900);
	add("dkoes_scoring","non_dir_h_bond(g=-0.7,_b=0,_c=8)", -0.153055);
	add("dkoes_scoring","ad4_solvation(d-sigma=3.6,_s/q=0.01097,_c=8)", 0.048934);
	add("dkoes_scoring","num_tors_sqr", 0.317267);
	add("dkoes_scoring","constant_term", -2.469020);
	/* trained with openbabel partial charges
	 weights.push_back(0.010764); //vdw
	 weights.push_back(-0.156861); //hbond
	 weights.push_back(0.062407); //desolvation
	 weights.push_back(0.337036); //tors sqr
	 weights.push_back(-2.231827); //constant
	 */

	add("dkoes_scoring_old","vdw(i=4,_j=8,_s=0,_^=100,_c=8)", 0.010607);
	add("dkoes_scoring_old","non_dir_h_bond(g=-0.7,_b=0,_c=8)", 0.197201);
	add("dkoes_scoring_old","num_tors_sqr", .285035);
	add("dkoes_scoring_old","constant_term", -2.585651);

	add("dkoes_fast","vdw(i=4,_j=8,_s=0,_^=100,_c=8)", 0.008962);
	add("dkoes_fast","non_dir_h_bond(g=-0.7,_b=0,_c=8)", 0.387739);
	add("dkoes_fast","num_tors_sqr", .285035);
	add("dkoes_fast","constant_term", -2.467357);

	add("ad4_scoring","vdw(i=6,_j=12,_s=0,_^=100,_c=8)", 0.1560);
	add("ad4_scoring","non_dir_h_bond_lj(o=-0.7,_^=100,_c=8)", -0.0974);
	add("ad4_scoring","ad4_solvation(d-sigma=3.5,_s/q=0.01097,_c=8)", 0.1159);
	add("ad4_scoring","electrostatic(i=1,_^=100,_c=8)", 0.1465);
	add("ad4_scoring","num_tors_add", 0.2744);
}

void builtin_scoring::print_functions(std::ostream& out)
{
	std::vector<std::string> names;
	for(funcmap::iterator itr = functions.begin(), en = functions.end(); itr != en; ++itr)
	{
		names.push_back(itr->first);
	}
	std::sort(names.begin(),names.end());

	for(unsigned i = 0, n = names.size(); i < n; i++)
	{
		out << names[i] << "\n";
	}
}

//global object for getting scoring functions
builtin_scoring builtin_scoring_functions;
